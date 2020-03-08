#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

class CentroidDecomposition
{
private:
    vector<vector<pair<int, ll>>> adj;
    vector<int> sz;
    vector<bool> del;

    void dfs1(int s, int parent)
    {
        sz[s] = 1;
        for (auto [e, _] : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            dfs1(e, s);
            sz[s] += sz[e];
        }
    }

    int dfs2(int s, int parent, int cap)
    {
        for (auto [e, _] : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            if (sz[e] > cap)
                return dfs2(e, s, cap);
        }
        return s;
    }

public:
    vector<int> p;
    CentroidDecomposition(int n) : adj(n + 1), sz(n + 1), del(n + 1), p(n + 1) {}

    void add_edge(int u, int v, ll w = 1)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs3(int s, int parent)
    {
        dfs1(s, -1);
        s = dfs2(s, -1, sz[s] / 2);
        del[s] = true;
        p[s] = parent;

        for (auto [e, w] : adj[s])
        {
            if (!del[e])
            {
                dfs3(e, s);
            }
        }
    }
};

struct Tree
{
    vector<vector<pii>> adj;
    vector<vector<int>> p;
    vector<int> depth, dis, color;
    vector<priority_queue<pii, vector<pii>, greater<pii>>> dp;

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

    Tree(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        p.resize(n + 1);

        for (int i = 0; i <= n; i++)
            p[i].resize(k + 1, 0);

        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
        color.resize(n + 1, 0);
        dp.resize(n + 1);
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    int LCA(int u, int v)
    {
        init();
        for (int i = k; i >= 0; i--)
            if (depth[p[u][i]] >= depth[v])
                u = p[u][i];

        for (int i = k; i >= 0; i--)
            if (depth[p[v][i]] >= depth[u])
                v = p[v][i];

        for (int i = k; i >= 0; i--)
            if (p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];

        return (u == v ? u : p[u][0]);
    }

    int raise_node(int u, int d)
    {
        init();
        for (int i = k, j; i >= 0 && (j = 1 << i); i--)
            if (j <= d)
                u = p[u][i], d -= j;
        return u;
    }

    ll dist(int a, int b)
    {
        init();
        int lca = LCA(a, b);
        return (ll)dis[a] + dis[b] - 2 * dis[lca];
    }

    void update(int u, vector<int> &par)
    {
        color[u] ^= 1;
        int v = u;
        while (v)
        {
            while (!dp[v].empty() && !color[dp[v].top().second])
                dp[v].pop();
            if (color[u])
                dp[v].push({dist(u, v), u});
            v = par[v];
        }
    }

    int query(int u, vector<int> &par)
    {
        int ret = INF;

        int v = u;
        while (v)
        {
            while (!dp[v].empty() && !color[dp[v].top().second])
                dp[v].pop();
            if (!dp[v].empty())
                ret = min((ll)ret, dp[v].top().first + dist(u, v));

            v = par[v];
        }
        return (ret == INF ? -1 : ret);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, q;
    cin >> n;

    CentroidDecomposition CD(n);
    Tree tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        CD.add_edge(u, v);
        tree.add_edge(u, v);
    }

    CD.dfs3(1, 0);
    auto &par = CD.p;

    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        if (x == 1)
        {
            tree.update(y, par);
        }
        else
        {
            cout << tree.query(y, par) << "\n";
        }
    }
}