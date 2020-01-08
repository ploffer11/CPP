#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class Tree
{
private:
    vector<vector<pii>> adj;
    vector<vector<int>> p;
    vector<int> depth, dis;
    bool flag = true;
    int root = 1, n;
    void dfs_numbering(int s, int dist, int d)
    {
        depth[s] = d;
        dis[s] = dist;

        for (auto [e, cost] : adj[s])
        {
            if (!depth[e])
            {
                p[e][0] = s;
                dfs_numbering(e, dist + cost, d + 1);
            }
        }
    }

    void init()
    {
        dfs_numbering(1, 0, 1);
        for (int i = 1; i <= 20; i++)
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
            p[i].resize(22, 0);

        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    int LCA(int a, int b)
    {
        if (flag)
        {
            flag = false;
            init();
        }

        if (depth[a] > depth[b])
            swap(a, b);

        int da = depth[a], db = depth[b];
        while (db - da)
        {
            int x = log2(db - da);
            int delta = 1 << x;

            db -= delta;
            b = p[b][x];
        }

        if (a == b)
            return a;

        for (int i = 20; i >= 0; i--)
            if (p[a][i] != p[b][i])
                a = p[a][i], b = p[b][i];

        return p[a][0];
    }

    ll dist(int a, int b)
    {
        int lca = LCA(a, b);
        return (ll)dis[a] + dis[b] - 2 * dis[lca];
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    Tree tree(n);

    for (int i = 1; i <= n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        tree.add_edge(a, b, c);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << tree.dist(u, v) << '\n';
    }
}