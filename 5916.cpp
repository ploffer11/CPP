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
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] += diff;
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
    int kth(int i, int s, int e, ll sum)
    {
        if (s == e)
            return s;
        int m = (s + e) / 2;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
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
    }

    int _query(int u, int v)
    {
        int ret = 0;
        while (hld[u] != hld[v])
        {
            ret += Tree.query(1, 1, n, num[hld[v]], num[v]);
            v = parent[hld[v]];
        }
        return ret + Tree.query(1, 1, n, num[u] + 1, num[v]);
    }

    void _update_range(int u, int v, int diff)
    {
        while (hld[u] != hld[v])
        {
            Tree.update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.update_range(1, 1, n, num[u] + 1, num[v], diff);
    }

public:
    int n, cnt, root;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), root(root)
    {
        hld[root] = parent[root] = root;
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init()
    {
        dfs1(root);
        dfs2(root);
    }

    int LCA(int u, int v)
    {
        while (hld[u] != hld[v])
        {
            if (depth[hld[u]] > depth[hld[v]])
                u = parent[hld[u]];
            else
                v = parent[hld[v]];
        }
        return (depth[u] < depth[v] ? u : v);
    }

    void update(int i, int v)
    {
        Tree.update_idx(1, 1, n, num[i], v);
    }

    void update_range(int u, int v, int diff)
    {
        int lca = LCA(u, v);
        _update_range(lca, u, diff);
        _update_range(lca, v, diff);
    }

    int query(int u, int v)
    {
        int lca = LCA(u, v);
        return _query(lca, u) + _query(lca, v);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    HeavyLightDecomposition HLD(n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        HLD.add_edge(u, v);
    }

    HLD.init();
    //   1(+2)
    //   4(+3)
    //2(+1) 3(+2)

    while (m--)
    {
        int x, y;
        char z;

        cin >> z >> x >> y;
        if (z == 'P')
            HLD.update_range(x, y, 1);
        else
            cout << HLD.query(x, y) << "\n";
    }
}