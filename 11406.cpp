#include <bits/stdc++.h>
using namespace std;

class Dinic
{
private:
    struct Edge
    {
        int cap, rev, flow, to;
        Edge(int t, int c) : cap(c), to(t), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<int> work, depth;

    int source, sink;

    void bfs()
    {
        fill(depth.begin(), depth.end(), -1);
        depth[source] = 0;
        queue<int> q;
        q.push(source);

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
                int f = dfs(e.to, min(e.cap - e.flow, flow));
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
    Dinic(int n, int m)
    {
        source = 0;
        sink = n + m + 1;

        depth.resize(sink + 1);
        adj.resize(sink + 1);
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
                //cout << "?";
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
    int n, m;
    cin >> n >> m;

    Dinic NetworkFlow(n, m);

    int x;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        NetworkFlow.add_edge(0, i, x);
    }

    for (int i = n + 1; i <= n + m; i++)
    {
        cin >> x;
        NetworkFlow.add_edge(i, n + m + 1, x);
    }

    for (int i = n + 1; i <= n + m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> x;
            if (x)
                NetworkFlow.add_edge(j, i, x);
        }
    }

    cout << NetworkFlow.max_flow();
}