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
    vector<ll> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
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
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return -INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

class HeavyLightDecomposition
{
public:
    void dfs1(int s)
    {
        weight[s] = 1;
        for (auto [e, _] : adj[s])
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

        for (auto [e, _] : adj[s])
            if (parent[e] == s && (E == -1 || weight[E] < weight[e]))
                E = e;

        if (E != -1)
            hld[E] = hld[s], dfs2(E);

        for (auto [e, _] : adj[s])
            if (parent[e] == s && e != E)
                hld[e] = e, dfs2(e);
    }

    int _query(int u, int v)
    {
        ll ret = -INF;
        while (hld[u] != hld[v])
        {
            ret = max(ret, Tree.query(1, 1, n, num[hld[v]], num[v]));
            v = parent[hld[v]];
        }
        return max(ret, Tree.query(1, 1, n, num[u] + 1, num[v]));
    }

public:
    int n, cnt, root;
    vector<vector<pii>> adj;
    vector<int> weight, parent, depth, num, idx, hld;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), root(root)
    {
        hld[root] = parent[root] = root;
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    void init()
    {
        dfs1(root);
        dfs2(root);

        for (int s = 1; s <= n; s++)
            for (auto [e, c] : adj[s])
                if (parent[e] == s)
                    update(e, c);
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

    int query(int u, int v)
    {
        int lca = LCA(u, v);
        return max(_query(lca, u), _query(lca, v));
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<tuple<int, int, int>> edge(n);
    HeavyLightDecomposition HLD(n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        HLD.add_edge(u, v, c);
        edge[i] = {u, v, c};
    }

    HLD.init();

    int q;
    cin >> q;
    while (q--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            auto [x, y, _] = edge[b];
            HLD.update((HLD.parent[x] == y ? x : y), c);
        }
        else
            cout << HLD.query(b, c) << "\n";
    }
}