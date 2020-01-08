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

    void init()
    {
        for (auto &vt : adj)
            for (auto &e : vt)
                e.flow = 0;
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

    void solve(int n, int m, int f)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                auto &e = adj[i][j];

                if (e.cap > 0 && e.flow > 0)
                {
                    auto copy = adj;
                    vector<int> save;

                    e.cap = 0;
                    for (int k = 0; k < j; k++)
                    {
                        if (adj[i][k].cap > 0 && adj[i][k].flow == 0)
                        {
                            save.push_back(k);
                            adj[i][k].cap = 0;
                        }
                    }
                    init();
                    int flow = max_flow();

                    for (auto k : save)
                        adj[i][k].cap = 1;
                    e.cap = 1;

                    if (f == flow)
                        continue;
                    else
                        adj = copy;
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (auto &e : adj[i])
            {
                if (e.cap > 0)
                    cout << e.flow;
            }
            cout << '\n';
        }
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m, f = 0, f2 = 0;
    cin >> n >> m;

    Dinic MF(n + m);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        f += x;
        MF.add_edge(MF.source, i, x);
        for (int j = n + 1; j <= n + m; j++)
        {
            MF.add_edge(i, j, 1);
        }
    }

    for (int i = n + 1; i <= n + m; i++)
    {
        int x;
        cin >> x;
        MF.add_edge(i, MF.sink, x);
        f2 += x;
    }

    int flow = MF.max_flow();

    if (flow != f || f != f2)
    {
        cout << -1;
        return 0;
    }
    else
    {
        MF.solve(n, m, f);
    }
}