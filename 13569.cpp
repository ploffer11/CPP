#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 1987654321;
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
    int source, sink, fake_source, fake_sink;

    Dinic(int n)
    {
        source = 0;
        fake_source = n - 1;
        fake_sink = n;
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
                int f = dfs(source, INF);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }

    int find_flow(int u, int v)
    {
        for (auto &e : adj[u])
            if (e.cap >= 0 && e.to == v)
                return e.flow;
        return INF;
    }
};

int n, m;
int f(int i, int j)
{
    return i * m + j + 1;
}

int rowL[205], rowR[205], columnL[205], columnR[205];
int sum[205];
int L[205][205];
int R[205][205];
int demand[100005];
int F;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;

    Dinic MF(2 * n * m + n + m + 2);
    MF.add_edge(MF.fake_sink, MF.fake_source, INF);

    double x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            L[i][j] = (int)x;
            R[i][j] = (int)(ceil(x));
        }
        cin >> x;
        rowL[i] = (int)x;
        rowR[i] = (int)(ceil(x));
    }

    for (int i = 0; i < m; i++)
    {
        cin >> x;
        columnL[i] = (int)x;
        columnR[i] = (int)(ceil(x));
    }

    const int OFFSET = 2 * n * m + 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = f(i, j);
            int v = f(i, j) + n * m;

            MF.add_edge(u, v, R[i][j] - L[i][j]);
            MF.add_edge(OFFSET + i, u, INF);
            MF.add_edge(v, OFFSET + n + j, INF);

            F += L[i][j];
            demand[u] += L[i][j];
            demand[v] -= L[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        MF.add_edge(MF.fake_source, OFFSET + i, rowR[i] - rowL[i]);
        F += rowL[i];
        demand[MF.fake_source] += rowL[i];
        demand[OFFSET + i] -= rowL[i];
    }

    for (int i = 0; i < m; i++)
    {
        MF.add_edge(OFFSET + n + i, MF.fake_sink, columnR[i] - columnL[i]);
        F += columnL[i];
        demand[OFFSET + n + i] += columnL[i];
        demand[MF.fake_sink] -= columnL[i];
    }

    for (int i = 1; i <= 2 * n * m + n + m + 2; i++)
    {
        if (demand[i] < 0)
            MF.add_edge(MF.source, i, -demand[i]);
        else if (demand[i] > 0)
            MF.add_edge(i, MF.sink, demand[i]);
    }

    int flow = MF.max_flow();
    cout << "flow: " << flow << " -> " << F << "\n";

    MF.source = MF.fake_source;
    MF.sink = MF.fake_sink;

    int add_flow = MF.max_flow();

    cout << F << " " << add_flow << "\n";

    for (int i = 0; i < n; i++)
    {
        ll y = 0;
        for (int j = 0; j < m; j++)
        {
            int x = L[i][j] + MF.find_flow(f(i, j), f(i, j) + n * m);
            y += x;
            sum[j] += x;
            cout << x << " ";
        }
        cout << y << "\n";
    }

    for (int i = 0; i < m; i++)
        cout << sum[i] << " ";
}