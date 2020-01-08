#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class PersistentSegmentTree
{
private:
    struct Node
    {
        Node() : v(0), left(0), right(0) {}
        int v;
        Node *left, *right;
    };
    vector<Node *> tree;
    vector<vector<int>> y;
    int xs, xe, ys, ye;
    bool flag = true;

    Node *make_tree(Node *cur, int ys, int ye, int y, int v)
    {
        if (!(ys <= y && y <= ye))
            return cur;
        Node *ret = new Node();
        if (ys == ye)
        {
            ret->v = cur->v + v;
            return ret;
        }
        int ym = (ys + ye) >> 1;
        ret->left = make_tree(cur->left, ys, ym, y, v);
        ret->right = make_tree(cur->right, ym + 1, ye, y, v);
        ret->v = (ret->left ? ret->left->v : 0) + (ret->right ? ret->right->v : 0);
        return ret;
    }

    Node *init_first_tree(int ys, int ye)
    {
        Node *ret = new Node();
        if (ys == ye)
        {
            ret->v = 0;
            return ret;
        }
        int ym = (ys + ye) >> 1;
        ret->left = init_first_tree(ys, ym);
        ret->right = init_first_tree(ym + 1, ye);
        ret->v = ret->left->v + ret->right->v;
        return ret;
    }

    int _query(Node *cur, int ys, int ye, int yl, int yr)
    {
        if (ys > yr || ye < yl || !cur)
            return 0;
        else if ((yl <= ys && ye <= yr))
            return cur->v;
        int ym = (ys + ye) >> 1;
        return _query(cur->left, ys, ym, yl, yr) + _query(cur->right, ym + 1, ye, yl, yr);
    }

    void init()
    {
        tree[xs] = init_first_tree(ys, ye);

        for (auto i : y[xs])
            tree[xs] = make_tree(tree[xs], xs, xe, i, 1);

        for (int i = 1; i <= xe; i++)
        {
            if (!y[i].empty())
            {
                tree[i] = make_tree(tree[i - 1], xs, xe, y[i][0], 1);
                for (int j = 1; j < y[i].size(); j++)
                    tree[i] = make_tree(tree[i], xs, xe, y[i][j], 1);
            }
            else
                tree[i] = tree[i - 1];
        }
    }

public:
    // make [0, n] x [0, n] segment tree
    PersistentSegmentTree(int n) : xs(0), xe(n), ys(0), ye(n)
    {
        tree.resize(n + 1);
        y.resize(n + 1);
    }

    void add_point(int x, int y)
    {
        this->y[x].push_back(y);
    }

    int query(int xl, int xr, int yl, int yr)
    {
        if (flag)
        {
            init();
            flag = false;
        }

        return _query(tree[xr], xs, xe, yl, yr) - _query(tree[xl - 1], xs, xe, yl, yr);
    }
};

const int N = 1'000'000;
vector<int> arr;
vector<int> vt;
vector<int> number[N + 1];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    PersistentSegmentTree Tree(N);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
        vt.push_back(x);
    }

    sort(vt.begin(), vt.end());
    vt.resize(unique(vt.begin(), vt.end()) - vt.begin());

    for (int i = 0; i < n; i++)
    {
        number[(lower_bound(vt.begin(), vt.end(), arr[i]) - vt.begin())]
            .push_back(i + 1);
    }

    for (int i = 0; i <= N; i++)
    {
        for (int j = 1; j < number[i].size(); j++)
        {
            Tree.add_point(number[i][j - 1], number[i][j]);
        }
    }

    int prev = 0;
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l += prev;

        int query = Tree.query(l, N, 0, r);
        cout << r - l + 1 - query << '\n';
        prev = r - l + 1 - query;
    }
}