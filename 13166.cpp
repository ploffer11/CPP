#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class Dinic
{
private:
    struct Edge
    {
        int to, rev, cap, flow, cost;
        Edge(int _to, int _cap, int _cost) : to(_to), cap(_cap), flow(0), cost(_cost) {}
    };

    vector<vector<Edge>> adj;
    vector<int> depth, work;

    void bfs(int k)
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
                if (e.cap - e.flow > 0 && depth[e.to] == -1 && e.cost <= k)
                {
                    depth[e.to] = depth[s] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int s, int flow, int k)
    {
        if (s == sink)
            return flow;

        for (int i = work[s]; i < adj[s].size(); i++, work[s]++)
        {
            auto &e = adj[s][i];

            if (depth[e.to] == depth[s] + 1 && e.cap - e.flow > 0 && e.cost <= k)
            {
                int f = dfs(e.to, min(flow, e.cap - e.flow), k);

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

    void add_edge(int u, int v, int cap, int cost)
    {
        adj[u].push_back(Edge(v, cap, cost));
        adj[v].push_back(Edge(u, 0, cost));
        adj[u].back().rev = adj[v].size() - 1;
        adj[v].back().rev = adj[u].size() - 1;
    }

    int max_flow(int k)
    {
        int flow = 0;
        while (1)
        {
            bfs(k);
            if (depth[sink] == -1)
                break;

            fill(work.begin(), work.end(), 0);
            while (1)
            {
                int f = dfs(source, 987654321, k);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }

    void init()
    {
        for (auto &vt : adj)
            for (auto &e : vt)
                e.flow = 0;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    using tt = tuple<int, int, int>;
    vector<tt> edges;
    for (int i = 1; i <= n; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        edges.push_back({i, a + n, b});
        edges.push_back({i, c + n, d});
    }

    Dinic MF(3 * n);

    for (int i = 1; i <= n; i++)
        MF.add_edge(MF.source, i, 1, 0);

    for (int i = n + 1; i <= 3 * n; i++)
        MF.add_edge(i, MF.sink, 1, 0);

    for (auto [u, v, c] : edges)
        MF.add_edge(u, v, 1, c);

    int MAX = 1'000'001;
    int s = 0, e = MAX;

    while (s <= e)
    {
        MF.init();
        int m = (s + e) / 2;
        int f = MF.max_flow(m);

        if (f == n)
            e = m - 1;
        else
            s = m + 1;
    }

    //cout << s << " " << e << '\n';
    cout << (s >= MAX ? -1 : s);
}