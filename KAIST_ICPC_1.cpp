#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class SegmentTree
{
private:
    vector<ll> tree, lazy;
    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += (e - s + 1) * lazy[i];
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
        lazy.resize(4 * (n + 1), 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);

        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] += diff;
            update_lazy(i, s, e);
        }

        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
};

class HeavyLightDecomposition
{
private:
    void dfs1(int s)
    {
        weight[s] = 1;
        for (auto e : adj[s])
        {
            if (!weight[e])
            {
                parent[e] = s;
                depth[e] = depth[s] + 1;
                dfs1(e);
                weight[s] += weight[e];
            }
        }
    }

    void dfs2(int s)
    {
        int E = -1;
        num[s] = ++cnt;
        idx[cnt] = s;

        for (auto e : adj[s])
            if (parent[e] == s && (E == -1 || weight[E] < weight[e]))
                E = e;

        if (E != -1)
            hld[E] = hld[s], dfs2(E);

        for (auto e : adj[s])
            if (parent[e] == s && e != E)
                hld[e] = e, dfs2(e);

        num_end[s] = cnt;
    }

    ll _query(int u, int v, bool out)
    {
        ll ret = 0;
        while (hld[u] != hld[v])
        {
            ret = ret + Tree.query(1, 1, n, num[hld[v]], num[v]);
            v = parent[hld[v]];
        }
        return ret + Tree.query(1, 1, n, num[u] + out, num[v]);
    }

    void _update_path(int u, int v, ll diff, bool out)
    {
        while (hld[u] != hld[v])
        {
            Tree.update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.update_range(1, 1, n, num[u] + out, num[v], diff);
    }

    void init()
    {
        if (flag)
            return;

        for (int i = 1; i <= n; i++)
            if (!weight[i])
                hld[i] = parent[i] = i, dfs1(i);

        for (int i = 1; i <= n; i++)
            if (!num[i])
                dfs2(i);

        flag = true;
    }

public:
    int n, cnt, root;
    bool flag, edge;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, bool edge, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), edge(edge)
    {
        flag = false;
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int LCA(int u, int v)
    {
        init();
        while (hld[u] != hld[v])
        {
            if (depth[hld[u]] > depth[hld[v]])
                u = parent[hld[u]];
            else
                v = parent[hld[v]];
        }
        return (depth[u] < depth[v] ? u : v);
    }

    void update_node(int i, ll diff)
    {
        init();
        Tree.update_idx(1, 1, n, num[i], diff);
    }

    void update_edge(int u, int v, ll diff)
    {
        init();
        update_node((parent[u] == v ? u : v), diff);
    }

    void update_subtree(int i, ll diff)
    {
        init();
        Tree.update_range(1, 1, n, num[i], num_end[i], diff);
    }

    void update_path(int u, int v, ll diff)
    {
        init();
        int lca = LCA(u, v);
        _update_path(lca, u, diff, true);
        _update_path(lca, v, diff, edge);
    }

    ll query_subtree(int i)
    {
        init();
        return Tree.query(1, 1, n, num[i], num_end[i]);
    }

    ll query_path(int u, int v)
    {
        init();
        int lca = LCA(u, v);
        return _query(lca, u, true) + _query(lca, v, edge);
    }
};

char board[505][505];

bool g(char x, char y, char i, char j)
{
    return (x == i && y == j);
}

int f(char x, char y)
{
    if (g(x, y, '1', '1') || g(x, y, '6', '9') || g(x, y, '9', '6') || g(x, y, '8', '8'))
        return 0;
    else if (g(x, y, '6', '6') || g(x, y, '7', '7') || g(x, y, '9', '9'))
        return 1;
    else
        return -1;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> board[i][j];

    if (n % 2 == 1 && m % 2 == 1)
    {
        if (board[n / 2 + 1][m / 2 + 1] != '8')
        {
            cout << "-1";
            return 0;
        }
    }

    int ans = 0;
    if (n % 2 == 1)
    {
        int R = n / 2 + 1;
        for (int i = 1; i <= m / 2; i++)
        {
            int cnt = f(board[R][i], board[R][m - i + 1]);
            if (cnt < 0)
            {
                cout << "-1";
                return 0;
            }
            ans += cnt;
        }
    }

    for (int i = 1; i <= n / 2; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            //cout << i << ", " << j << " : " << n - i + 1 << ", " << m - j + 1 << "\n";
            int cnt = f(board[i][j], board[n - i + 1][m - j + 1]);
            if (cnt < 0)
            {
                cout << "-1";
                return 0;
            }
            ans += cnt;
        }
    }
    cout << ans;
}