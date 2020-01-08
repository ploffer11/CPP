#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#define endl '\n'
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

    int _kth(Node *tree1, Node *tree2, int ys, int ye, int k)
    {
        int ym = (ys + ye) >> 1;

        if (ys == ye)
            return ys;

        if (tree2->left->v - tree1->left->v >= k)
            return _kth(tree1->left, tree2->left, ys, ym, k);
        else
            return _kth(tree1->right, tree2->right, ym + 1, ye, k - (tree2->left->v - tree1->left->v));
    }

    int _xor_query(Node *tree1, Node *tree2, int ys, int ye, int bit, int x)
    {
        if (ys == ye)
            return ys;

        int ym = (ys + ye) >> 1;

        if (tree2->right->v - tree1->right->v == 0 || (tree2->left->v - tree1->left->v > 0 && ((1 << bit) & x)))
            return _xor_query(tree1->left, tree2->left, ys, ym, bit - 1, x);
        else
            return _xor_query(tree1->right, tree2->right, ym + 1, ye, bit - 1, x);
    }

public:
    // make [0, n] x [0, n] segment tree
    PersistentSegmentTree(int n) : xs(0), xe(n), ys(0), ye(n)
    {
        tree.resize(n + 1);
        tree[xs] = init_first_tree(ys, ye);
    }

    // query [xl, xr] x [yl, yr]
    int query(int xl, int xr, int yl, int yr)
    {
        return _query(tree[xr], xs, xe, yl, yr) - _query(tree[xl - 1], xs, xe, yl, yr);
    }

    // find min(y) that satisfies query [xl, xr] x [0, y] >= k
    int kth(int xl, int xr, int k)
    {
        return _kth(tree[xl - 1], tree[xr], ys, ye, k);
    }

    void update(int x, int y)
    {
        tree[x] = make_tree(tree[x - 1], ys, ye, y, 1);
    }

    int xor_query(int xl, int xr, int x)
    {
        return _xor_query(tree[xl - 1], tree[xr], ys, ye, 18, x);
    }
};

vector<int> arr;
const int N = (1 << 19) - 1;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    PersistentSegmentTree Tree(N);

    int m;
    cin >> m;
    while (m--)
    {
        int x;
        cin >> x;

        if (x == 1)
        {
            int x;
            cin >> x;
            arr.push_back(x);
            Tree.update(arr.size(), x);
        }

        else if (x == 2)
        {
            int l, r, x;
            cin >> l >> r >> x;

            cout << Tree.xor_query(l, r, x) << endl;
        }

        else if (x == 3)
        {
            int k;
            cin >> k;
            while (k--)
                arr.pop_back();
        }

        else if (x == 4)
        {
            int l, r, x;
            cin >> l >> r >> x;
            cout << Tree.query(l, r, 0, x) << /*" <-- 4" <<*/ endl;
        }

        else
        {
            int l, r, k;
            cin >> l >> r >> k;
            cout << Tree.kth(l, r, k) << /*" <-- 5" <<*/ endl;
        }
    }
}