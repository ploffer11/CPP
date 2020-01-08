#include <bits/stdc++.h>
using namespace std;

class Dinic
{
private:
    struct Edge
    {
        int to, rev, flow, cap;
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
                    q.push(e.to);
                    depth[e.to] = depth[s] + 1;
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
    Dinic(int n)
    {
        source = 0;
        sink = n + 1;

        depth.resize(sink + 1);
        work.resize(sink + 1);
        adj.resize(sink + 1);
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

            // cout << flow << " " << depth[sink] << " ";

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
    while (1)
    {
        int n, m;
        cin >> n >> m;
        if (n + m == 0)
            break;

        Dinic NetworkFlow(n);

        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            if (x)
                NetworkFlow.add_edge(0, i, 1);
            else
                NetworkFlow.add_edge(i, n + 1, 1);
        }

        while (m--)
        {
            int a, b;
            cin >> a >> b;
            NetworkFlow.add_edge(a, b, 1);
            NetworkFlow.add_edge(b, a, 1);
            //cout << "hello\n";
        }
        cout << NetworkFlow.max_flow() << '\n';
    }
}