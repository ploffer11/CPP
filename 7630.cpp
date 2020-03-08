#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

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
};

int parent[100005];
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

    while (1)
    {
        memset(parent, -1, sizeof(parent));
        tuple<int, int, int> edge;

        int n;
        cin >> n;

        if (n == 0)
            return 0;

        Tree tree(n);

        for (int i = 1; i <= n; i++)
        {

            int u, v, w;
            cin >> u >> v >> w;
            u++;
            v++;
            if (find(u) != find(v))
            {
                uni(u, v);
                tree.add_edge(u, v, w);
            }
            else
            {
                edge = {u, v, w};
            }
        }

        auto [x, y, z] = edge;
        int q;
        cin >> q;
        while (q--)
        {
            int u, v;
            cin >> u >> v;
            u++;
            v++;

            cout << min({tree.dist(u, v),
                         tree.dist(u, x) + z + tree.dist(y, v),
                         tree.dist(u, y) + z + tree.dist(x, v)})
                 << "\n";
        }
    }
}