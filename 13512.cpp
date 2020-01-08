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
        return ret + Tree.query(1, 1, n, num[u], num[v]);
    }

    int _query2(int u, int v, int q)
    {
        while (hld[u] != hld[v])
        {
            int q2 = Tree.query(1, 1, n, num[hld[v]], num[v]);

            if (q == q2)
                return Tree.kth(1, 1, n, 1 + Tree.query(1, 1, n, 1, num[hld[v]] - 1));

            q -= q2;
            v = parent[hld[v]];
        }
        return Tree.kth(1, 1, n, 1 + Tree.query(1, 1, n, 1, num[u] - 1));
    }

    void _update_range(int u, int v, int diff)
    {
        while (hld[u] != hld[v])
        {
            Tree.update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.update_range(1, 1, n, num[u], num[v], diff);
    }

    void init()
    {
        if (!flag)
        {
            dfs1(root);
            dfs2(root);
        }
        flag = true;
    }

public:
    int n, cnt, root;
    bool flag;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), root(root)
    {
        hld[root] = parent[root] = root;
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

    void update(int i)
    {
        init();
        if (Tree.query(1, 1, n, num[i], num[i]))
            Tree.update_idx(1, 1, n, num[i], -1);
        else
            Tree.update_idx(1, 1, n, num[i], 1);
    }

    void update_range(int u, int v, int diff)
    {
        init();
        int lca = LCA(u, v);
        _update_range(lca, u, diff);
        _update_range(lca, v, diff);
        _update_range(lca, lca, -diff);
    }

    int query(int v)
    {
        init();
        int q = _query(1, v);
        if (q == 0)
            return -1;
        else
            return idx[_query2(1, v, q)];
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    HeavyLightDecomposition HLD(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        HLD.add_edge(u, v);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        if (x == 1)
            HLD.update(y);
        else
            cout << HLD.query(y) << "\n";
    }
}