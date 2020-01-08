#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int unsigned long long
using namespace std;
using ll = unsigned long long;
using pii = pair<int, int>;
const int INF = 987654321;
const long long MOD = (long long)1 << 32;

class SegmentTree
{
private:
    vector<ll> tree, sum_lazy, mul_lazy;
    void update_lazy(int i, int s, int e)
    {
        tree[i] %= MOD;
        if (sum_lazy[i] != 0 || mul_lazy[i] != 1)
        {
            sum_lazy[i] %= MOD;
            mul_lazy[i] %= MOD;
            tree[i] *= mul_lazy[i];
            tree[i] %= MOD;

            if (s != e)
            {
                sum_lazy[2 * i] %= MOD;
                sum_lazy[2 * i] *= mul_lazy[i];
                sum_lazy[2 * i] %= MOD;
                sum_lazy[2 * i + 1] %= MOD;
                sum_lazy[2 * i + 1] *= mul_lazy[i];
                sum_lazy[2 * i + 1] %= MOD;
                mul_lazy[2 * i] %= MOD;
                mul_lazy[2 * i] *= mul_lazy[i];
                mul_lazy[2 * i] %= MOD;
                mul_lazy[2 * i + 1] %= MOD;
                mul_lazy[2 * i + 1] *= mul_lazy[i];
                mul_lazy[2 * i + 1] %= MOD;
            }

            mul_lazy[i] = 1;

            tree[i] += (e - s + 1) * sum_lazy[i];
            tree[i] %= MOD;

            if (s != e)
            {
                sum_lazy[2 * i] %= MOD;
                sum_lazy[2 * i] += sum_lazy[i];
                sum_lazy[2 * i] %= MOD;
                sum_lazy[2 * i + 1] %= MOD;
                sum_lazy[2 * i + 1] += sum_lazy[i];
                sum_lazy[2 * i + 1] %= MOD;
            }

            sum_lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
        sum_lazy.resize(4 * (n + 1), 0);
        mul_lazy.resize(4 * (n + 1), 1);
    }

    void sum_update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);

        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            sum_lazy[i] %= MOD;
            sum_lazy[i] += diff;
            sum_lazy[i] %= MOD;
            update_lazy(i, s, e);
        }

        else
        {
            int m = (s + e) / 2;
            sum_update_range(2 * i, s, m, l, r, diff);
            sum_update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = (tree[2 * i] + tree[2 * i + 1]) % MOD;
        }
    }

    void mul_update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);

        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            mul_lazy[i] %= MOD;
            mul_lazy[i] *= diff;
            mul_lazy[i] %= MOD;
            sum_lazy[i] %= MOD;
            sum_lazy[i] *= diff;
            sum_lazy[i] %= MOD;
            update_lazy(i, s, e);
        }

        else
        {
            int m = (s + e) / 2;
            mul_update_range(2 * i, s, m, l, r, diff);
            mul_update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = (tree[2 * i] + tree[2 * i + 1]) % MOD;
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i] % MOD;
        else
        {
            int m = (s + e) / 2;
            return (query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r)) % MOD;
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

    ll _query(int u, int v)
    {
        ll ret = 0;
        while (hld[u] != hld[v])
        {
            ret = (ret + Tree.query(1, 1, n, num[hld[v]], num[v])) % MOD;
            v = parent[hld[v]];
        }
        return (ret + Tree.query(1, 1, n, num[u], num[v])) % MOD;
    }

    void _sum_update_path(int u, int v, ll diff, bool out)
    {
        while (hld[u] != hld[v])
        {
            Tree.sum_update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.sum_update_range(1, 1, n, num[u] + out, num[v], diff);
    }

    void _mul_update_path(int u, int v, ll diff, bool out)
    {
        while (hld[u] != hld[v])
        {
            Tree.mul_update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.mul_update_range(1, 1, n, num[u] + out, num[v], diff);
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
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), root(root)
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

    void sum_update_subtree(int i, ll diff)
    {
        init();
        Tree.sum_update_range(1, 1, n, num[i], num_end[i], diff);
    }

    void mul_update_subtree(int i, ll diff)
    {
        init();
        Tree.mul_update_range(1, 1, n, num[i], num_end[i], diff);
    }

    void sum_update_path(int u, int v, ll diff)
    {
        init();
        int lca = LCA(u, v);
        _sum_update_path(lca, u, diff, false);
        _sum_update_path(lca, v, diff, true);
    }

    void mul_update_path(int u, int v, ll diff)
    {
        init();
        int lca = LCA(u, v);
        _mul_update_path(lca, u, diff, false);
        _mul_update_path(lca, v, diff, true);
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
        return ((_query(lca, u) + _query(lca, v)) % MOD + MOD - _query(lca, lca)) % MOD;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    HeavyLightDecomposition HLD(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        HLD.add_edge(u, v);
    }

    while (q--)
    {
        int command, x, y;
        ll v;
        cin >> command;

        if (command == 1)
        {
            cin >> x >> v;
            HLD.sum_update_subtree(x, v);
        }
        else if (command == 2)
        {
            cin >> x >> y >> v;
            HLD.sum_update_path(x, y, v);
        }
        else if (command == 3)
        {
            cin >> x >> v;
            HLD.mul_update_subtree(x, v);
        }
        else if (command == 4)
        {
            cin >> x >> y >> v;
            HLD.mul_update_path(x, y, v);
        }
        else if (command == 5)
        {
            cin >> x;
            cout << HLD.query_subtree(x) % MOD << "\n";
        }
        else
        {
            cin >> x >> y;
            cout << HLD.query_path(x, y) % MOD << "\n";
        }
    }
}