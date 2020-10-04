#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
    int kth(int i, int s, int e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        int m = (s + e) >> 1;
        update_lazy(2 * i, s, m);
        update_lazy(2 * i + 1, m + 1, e);
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

class CentroidDecomposition
{
private:
    vector<vector<int>> adj;
    vector<int> sz, p;
    vector<bool> del;

    void dfs1(int s, int parent)
    {
        sz[s] = 1;
        for (auto e : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            dfs1(e, s);
            sz[s] += sz[e];
        }
    }

    int dfs2(int s, int parent, int cap)
    {
        for (auto e : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            if (sz[e] > cap)
                return dfs2(e, s, cap);
        }
        return s;
    }

    void dfs3(int s, int parent)
    {
        dfs1(s, -1);
        s = dfs2(s, -1, sz[s] / 2);
        del[s] = true;
        p[s] = parent;

        for (auto e : adj[s])
        {
            if (!del[e])
            {
                dfs3(e, s);
            }
        }
    }
public:
    CentroidDecomposition(int n) : adj(n + 1), sz(n + 1), del(n + 1), p(n + 1) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> make_centroid_tree()
    {
        dfs3(1, 0);
        return p;
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

class Tree
{
private:
    vector<vector<pii>> adj;
    vector<vector<int>> p;
    vector<int> depth, dis;
    bool flag = true;
    int n, k = 20;

    void dfs(int s, ll dist, int d)
    {
        depth[s] = d;
        dis[s] = dist;

        for (auto [e, cost] : adj[s])
        {
            if (!depth[e])
            {
                p[e][0] = s;
                dfs(e, dist + cost, d + 1);
            }
        }
    }

    void init()
    {
        if (!flag)
            return;

        flag = false;
        dfs(1, 0, 1);
        for (int i = 1; i <= k; i++)
            for (int me = 1; me <= n; me++)
                p[me][i] = p[p[me][i - 1]][i - 1];
    }

public:
    vector<pair<ll, int>> dp;
    Tree(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        p.resize(n + 1);

        for (int i = 0; i <= n; i++)
            p[i].resize(k + 1, 0);

        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
        dp.resize(n + 1, {INF, 0});
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    int LCA(int u, int v, HeavyLightDecomposition &HLD)
    {
        init();
        return HLD.LCA(u, v);
    }

    int raise_node(int u, int d)
    {
        init();
        for (int i = k, j; i >= 0 && (j = 1 << i); i--)
            if (j <= d)
                u = p[u][i], d -= j;
        return u;
    }

    ll dist(int a, int b, HeavyLightDecomposition &HLD)
    {
        init();
        int lca = HLD.LCA(a, b);
        return (ll)dis[a] + dis[b] - 2 * dis[lca];
    }

    vector<int> backup;
    void update(int i, vector<int> &P, HeavyLightDecomposition &HLD)
    {
        init();
        int j = i;
        while (i)
        {
            dp[i] = min(dp[i], {HLD.query_path(i, j), j});
            backup.push_back(i);
            i = P[i];
        }
    }

    ll query(int i, vector<int> &P, HeavyLightDecomposition &HLD)
    {
        init();
        ll ret = INF;
        int j = i;
        while (i)
        {
            if (dp[i].first != INF)
                ret = min(ret, HLD.query_path(dp[i].second, j));
            i = P[i];
        }
        return ret;
    }

    void clear()
    {
        for (auto i : backup)
            dp[i] = {INF, 0};
        backup.clear();
    }
};


char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}


int readInt() {
    int ret = 0, flg = 1;
    char now = read();

    while (isspace(now)) now = read();
    if (now == '-') flg = -1, now = read();
    while (now >= 48 && now <= 57) {
        ret = ret * 10 + now - 48;
        now = read();
    }
    return ret * flg;
}

main()
{
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    int n, q;
    // cin >> n >> q;
    n = readInt(), q = readInt();

    CentroidDecomposition CD(n);
    Tree tree(n);
    HeavyLightDecomposition HLD(n, true);
        
    vector<tuple<int, int, int>> edge;
    for (int i = 1, u, v, w; i <= n - 1; i++)
    {
        u = readInt(), v = readInt(), w = readInt();
        u++, v++;
        CD.add_edge(u, v);
        HLD.add_edge(u, v);
        tree.add_edge(u, v, w);
        edge.push_back({u, v, w});
    }
    
    for (auto [u, v, w] : edge)
        HLD.update_edge(u, v, w);

    vector<int> P = CD.make_centroid_tree();

    while (q--)
    {
        int x, y;
        // cin >> x >> y;
        x = readInt(), y = readInt();
        
        vector<int> X(x), Y(y);
        for (int i = 0; i < x; i++)
            X[i] = readInt(), X[i]++;
        for (int i = 0; i < y; i++)
            Y[i] = readInt(), Y[i]++;
        
        for (auto i : X)
            tree.update(i, P, HLD);
    
        ll ans = INF;
        for (auto i : Y)
            ans = min(ans, tree.query(i, P, HLD));
        
        printf("%lld\n", ans);
        tree.clear();
    }
}