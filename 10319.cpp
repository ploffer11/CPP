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
    int source, sink, fake_source;

    Dinic(int n, int t)
    {
        source = 0;
        fake_source = n * (t + 1) + 1;
        sink = fake_source + 1;

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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, start, people, time;
        cin >> n >> start >> people >> time;

        Dinic MF(n, time);
        MF.add_edge(MF.source, MF.fake_source, people);

        int m;
        cin >> m;
        while (m--)
        {
            int x;
            cin >> x;
            for (int i = 0; i <= time; i++)
            {
                int node = i * n + x;
                MF.add_edge(node, MF.sink, INF);
            }
        }

        int r;
        cin >> r;
        while (r--)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            if (b == start)
                continue;

            else if (a == start)
            {
                for (int i = d; i <= time; i++)
                {
                    int node = i * n + b;
                    MF.add_edge(MF.fake_source, node, c);
                }
            }

            else
            {
                for (int i = 0; i <= time; i++)
                {
                    if (i + d > time)
                        break;

                    int node1 = i * n + a;
                    int node2 = (i + d) * n + b;
                    MF.add_edge(node1, node2, c);
                }
            }
        }

        cout << MF.max_flow() << '\n';
    }
}
