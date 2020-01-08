#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#define int long long
using namespace std;
using ll = long long;
const ll INF = 12345678987654321;

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

    int max_flow(int a, int n)
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

        cout << a + flow << '\n';

        for (int i = 1; i <= n; i++)
            if (depth[i] != -1)
                cout << i << " ";

        cout << '\n';

        for (int i = 1; i <= n; i++)
            if (depth[i] == -1)
                cout << i << " ";

        cout << '\n';

        return flow;
    }
};

int cap[505][505];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    Dinic MF(n);
    vector<int> red, blue, mid;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
            mid.push_back(i);
        else
            (x == 1 ? red : blue).push_back(i);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> cap[i][j];

    for (auto i : red)
        MF.add_edge(MF.source, i, INF);

    for (auto i : blue)
        MF.add_edge(i, MF.sink, INF);

    for (auto i : red)
        for (auto j : mid)
            MF.add_edge(i, j, cap[i][j]);

    for (auto i : mid)
        for (auto j : blue)
            MF.add_edge(i, j, cap[i][j]);

    for (auto i : mid)
        for (auto j : mid)
            if (i != j)
                MF.add_edge(i, j, cap[i][j]);

    for (auto i : red)
        for (auto j : blue)
            MF.add_edge(i, j, cap[i][j]);

    MF.max_flow(0, n);
}