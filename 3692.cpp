#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class Dinic
{
private:
    struct Edge
    {
        int to, rev, cap, flow;
        Edge(int _to, int _cap) : to(_to), cap(_cap), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<int> depth, work;

    void bfs()
    {
        fill(depth.begin(), depth.end(), -1);

        queue<int> q;
        q.push(source);
        depth[source] = 0;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();

            for (auto &e : adj[s])
            {
                if (e.cap - e.flow > 0 && depth[e.to] == -1)
                {
                    depth[e.to] = depth[s] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int s, int flow)
    {
        if (s == sink)
            return flow;

        for (int i = work[s]; i < adj[s].size(); i++, work[s]++)
        {
            auto &e = adj[s][i];

            if (depth[e.to] > depth[s] && e.cap - e.flow > 0)
            {
                int f = dfs(e.to, min(flow, e.cap - e.flow));

                if (f < 0)
                    continue;

                e.flow += f;
                adj[e.to][e.rev].flow -= f;

                return f;
            }
        }

        return -1;
    }

public:
    int source, sink;

    Dinic(int n)
    {
        source = 0;
        sink = n + 1;

        adj.resize(sink + 1);
        depth.resize(sink + 1);
        work.resize(sink + 1);
    }

    void add_edge(int u, int v, int cap)
    {
        adj[u].push_back(Edge(v, cap));
        adj[v].push_back(Edge(u, 0));
        adj[u].back().rev = adj[v].size() - 1;
        adj[v].back().rev = adj[u].size() - 1;
    }

    int max_flow()
    {
        int flow = 0;
        while (1)
        {
            bfs();
            if (depth[sink] == -1)
                break;

            fill(work.begin(), work.end(), 0);
            while (1)
            {
                int f = dfs(source, 987654321);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }
};

ld dist(pll a, pll b)
{
    return sqrt(
        (a.first - b.first) * (a.first - b.first) +
        (a.second - b.second) * (a.second - b.second));
}

pll points[105];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        ld d;

        cin >> n >> d;

        int total = 0;
        vector<tuple<int, int, int>> edges;
        for (int i = 1; i <= n; i++)
        {
            ll x, y, a, b;
            cin >> x >> y >> a >> b;
            points[i] = {x, y};
            edges.push_back({0, i, a});
            edges.push_back({i, n + i, b});
            total += a;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (dist(points[i], points[j]) <= d)
                {
                    edges.push_back({i + n, j, INF});
                    edges.push_back({j + n, i, INF});
                }
            }
        }

        vector<int> ans;
        for (int i = 1; i <= n; i++)
        {
            Dinic MF(2 * n);
            for (auto [u, v, c] : edges)
            {
                MF.add_edge(u, v, c);
            }
            MF.add_edge(i, MF.sink, INF);

            if (MF.max_flow() == total)
                ans.push_back(i);
        }

        if (ans.empty())
        {
            cout << "-1\n";
        }

        else
        {
            for (auto i : ans)
                cout << i - 1 << " ";
            cout << '\n';
        }
    }
}