#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;

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

    void bfs()
    {
        fill(depth.begin(), depth.end(), -1);
        queue<int> q;
        depth[source] = 0;
        q.push(source);

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
    int source, sink;
    // 0 source
    // 1 ~ m     0단축사

    // m+1 ~ 2m     1단축사
    // 2m+1 ~ 3m    2단 축사
    // nm ~ (n+1)m  n단축사

    // (n+1)m + 1 ~ (n+1)m + n 사람
    // (n+1)m + n + 1 sink
    Dinic(int n, int m)
    {
        source = 0;
        sink = (n + 1) * (m + 1);

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
                int f = dfs(source, INF);
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
    cin >> m >> n;

    Dinic NetworkFlow(n, m);

    // 0 source
    // 1 ~ m     0단축사

    // m+1 ~ 2m     1단축사
    // 2m+1 ~ 3m    2단 축사
    // nm+1 ~ (n+1)m  n단축사

    // (n+1)m + 1 ~ (n+1)m + n 사람
    // (n+1)m + n + 1 sink

    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        NetworkFlow.add_edge(NetworkFlow.source, i, x);
    }

    for (int i = 1; i <= n; i++)
    {
        vector<int> vt;
        int person = (n + 1) * m + i;
        int A, B;

        cin >> A;

        vt.clear();
        vt.resize(A);
        for (int j = 0; j < A; j++)
        {
            cin >> vt[j];
            NetworkFlow.add_edge(i * m + vt[j], person, INF);
        }

        if (i != n)
        {
            for (auto u : vt)
            {
                for (auto v : vt)
                {
                    if (u == v)
                        continue;
                    NetworkFlow.add_edge(i * m + u, (i + 1) * m + v, INF);
                }
            }
        }

        cin >> B;
        NetworkFlow.add_edge(person, NetworkFlow.sink, B);

        for (int j = 1; j <= m; j++)
        {
            NetworkFlow.add_edge((i - 1) * m + j, i * m + j, INF);
        }
    }

    cout << NetworkFlow.max_flow();
}