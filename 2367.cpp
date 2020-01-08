#include <bits/stdc++.h>
using namespace std;

class Dinic
{
private:
    struct Edge
    {
        int to, rev, cap, flow;
        Edge(int t, int c) : to(t), cap(c), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<int> depth, work;
    int source, sink;

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
                if (depth[e.to] == -1 && e.cap - e.flow > 0)
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

        for (int &i = work[s]; i < adj[s].size(); i++)
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
    Dinic(int n, int m, int k)
    {
        source = 0;
        sink = n + m + 1;

        adj.resize(sink + 1);
        depth.resize(sink + 1);
        work.resize(sink + 1);

        for (int i = 1; i <= n; i++)
        {
            add_edge(source, i, k);
        }
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
    int n, m, k;
    cin >> n >> k >> m;

    Dinic NetworkFlow(n, m, k);

    for (int i = n + 1; i <= n + m; i++)
    {
        int x;
        cin >> x;
        NetworkFlow.add_edge(i, n + m + 1, x);
    }

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        while (x--)
        {
            int y;
            cin >> y;
            NetworkFlow.add_edge(i, n + y, 1);
        }
    }

    cout << NetworkFlow.max_flow();
}