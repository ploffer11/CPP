#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int x[200000], y[200000], lca[200000];
int num_inters[200000], ps_inters[200000];
map<pii, int> mp;

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
    Tree(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        p.resize(n + 1);

        for (int i = 0; i <= n; i++)
            p[i].resize(k + 1, 0);

        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
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

        if (u == v)
            return u;

        for (int i = k; i >= 0; i--)
            if (p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];

        return p[u][0];
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

    int f(int lca, int u)
    {
        return (lca == u ? -1 : raise_node(u, depth[u] - depth[lca] - 1));
    }

    void dfs2(int s, int x)
    {
        ps_inters[s] = x;
        for (auto [e, cost] : adj[s])
            if (s == p[e][0])
                dfs2(e, x + num_inters[e]);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m;

    Tree tree(n);
    q = m - (n - 1);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }

    ll ans = 0;
    for (int i = 1; i <= q; i++)
    {
        cin >> x[i] >> y[i];
        lca[i] = tree.LCA(x[i], y[i]);

        int X = tree.f(lca[i], x[i]);
        int Y = tree.f(lca[i], y[i]);

        if (X != -1)
            ans -= ++num_inters[X];

        if (Y != -1)
            ans -= ++num_inters[Y];

        if (X != -1 && Y != -1)
            ans -= mp[{min(X, Y), max(X, Y)}]++;
    }

    tree.dfs2(1, 0);
    for (int i = 1; i <= q; i++)
        ans += ps_inters[x[i]] + ps_inters[y[i]] - 2 * ps_inters[lca[i]];
    cout << ans;
}
