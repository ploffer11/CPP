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
            tree[xs] = make_tree(tree[xs], ys, ye, i, 1);

        for (int i = 1; i <= xe; i++)
        {
            if (!y[i].empty())
            {
                tree[i] = make_tree(tree[i - 1], ys, ye, y[i][0], 1);
                for (int j = 1; j < y[i].size(); j++)
                    tree[i] = make_tree(tree[i], ys, ye, y[i][j], 1);
            }
            else
                tree[i] = tree[i - 1];
        }
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

    // query [xl, xr] x [yl, yr]
    int query(int xl, int xr, int yl, int yr)
    {
        if (flag)
        {
            init();
            flag = false;
        }

        return _query(tree[xr], xs, xe, yl, yr) - _query(tree[xl - 1], xs, xe, yl, yr);
    }

    // find min(y) that satisfies query [xl, xr] x [0, y] >= k
    int kth(int xl, int xr, int k)
    {
        if (flag)
        {
            init();
            flag = false;
        }

        return _kth(tree[xl - 1], tree[xr], ys, ye, k);
    }
};

const int MAX = 200'005;
int cnt = 0;
int color[MAX], l[MAX], r[MAX];
vector<int> adj[MAX];

void dfs(int s)
{
    l[s] = ++cnt;
    for (auto e : adj[s])
        if (!l[e])
            dfs(e);
    r[s] = cnt;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    PersistentSegmentTree Tree(MAX);

    int n, m, c;
    cin >> n >> m >> c;

    for (int i = 1; i <= n; i++)
        cin >> color[i];

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i <= n; i++)
        Tree.add_point(l[i], color[i]);

    ll ans = 0;
    while (m--)
    {
        int v, c;
        cin >> v >> c;
        ans += Tree.query(l[v], r[v], 0, c);
        ans %= MOD;
    }

    cout << ans;
}