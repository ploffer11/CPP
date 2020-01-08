#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;

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
    bool flag, node;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, bool node, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), node(node)
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
        _update_path(lca, u, diff, false);
        _update_path(lca, v, diff, node);
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
        return _query(lca, u, false) + _query(lca, v, node);
    }
};

int parent[30005];
ll ans[300005];

const int YES = -1;
const int NO = -2;
const int IMPOSSIBLE = -3;

int find(int me)
{
    if (parent[me] < 0)
        return me;
    else
        return parent[me] = find(parent[me]);
}

void uni(int a, int b)
{
    a = find(a), b = find(b);
    if (a != b)
    {
        parent[a] += parent[b];
        parent[b] = a;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int cnt = 0;
    vector<tuple<int, int, int, int>> query;

    int n;
    cin >> n;
    HeavyLightDecomposition HLD(n, 1);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        query.push_back({1, i, x, -1});
    }

    int q;
    cin >> q;

    while (q--)
    {
        string inp;
        int a, b;
        cin >> inp;

        if (inp[0] == 'e')
        {
            cin >> a >> b;
            if (find(a) != find(b))
                ans[cnt++] = IMPOSSIBLE;
            else
                query.push_back({2, a, b, cnt++});
        }

        else if (inp[0] == 'b')
        {
            cin >> a >> b;
            if (find(a) != find(b))
            {
                ans[cnt++] = YES;
                HLD.add_edge(a, b);
                uni(a, b);
            }
            else
            {
                ans[cnt++] = NO;
            }
        }

        else if (inp[0] == 'p')
        {
            cin >> a >> b;
            query.push_back({1, a, b, -1});
        }
    }

    for (auto [a, b, c, d] : query)
    {
        if (a == 1)
            HLD.update_node(b, c);

        else
            ans[d] = HLD.query_path(b, c);
    }

    for (int i = 0; i < cnt; i++)
    {
        if (ans[i] == YES)
            cout << "yes\n";
        else if (ans[i] == NO)
            cout << "no\n";
        else if (ans[i] == IMPOSSIBLE)
            cout << "impossible\n";
        else
            cout << ans[i] << "\n";
    }
}
