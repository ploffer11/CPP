#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> t;

vector<t> edges;
vector<int> adj[1005];
bool visit[1005];

bool bfs(int s, int e)
{
    memset(visit, 0, sizeof(visit));
    queue<int> q;
    q.push(s);
    visit[s] = 1;

    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        for (auto e : adj[s])
        {
            if (!visit[e])
            {
                visit[e] = visit[s] + 1;
                q.push(e);
            }
        }
    }

    return (bool)visit[e];
}

class Dinic
{
private:
    struct Edge
    {
        int rev, flow, cap, to;
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
    Dinic(int n, int a, int b)
    {
        source = a;
        sink = b;

        adj.resize(n);
        depth.resize(n);
        work.resize(n);
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

            fill(work.begin(), work.end(), 0);
            if (depth[sink] == -1)
                break;
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
    int t;
    cin >> t;
    while (t--)
    {
        edges.clear();
        int n, e, a, b;
        cin >> n >> e >> a >> b;

        Dinic NetworkFlow(n, a, b);

        while (e--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            NetworkFlow.add_edge(x, y, z);
            edges.push_back({x, y, z});
        }

        int flow = NetworkFlow.max_flow();

        int s = 0;
        e = 100000000;
        while (s <= e)
        {
            int m = (s + e) / 2;

            for (int i = 0; i <= 1000; i++)
                adj[i].clear();

            for (auto [u, v, w] : edges)
            {
                if (w >= m)
                {
                    adj[u].push_back(v);
                }
            }

            if (bfs(a, b))
                s = m + 1;
            else
                e = m - 1;
        }

        //cout << s << "< - >" << e << endl;
        printf("%.3lf\n", (double)flow / e);
    }
}