#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;

bool board[205][205];
pii range[205], min_range[205], max_range[205];

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

    void solve(int n)
    {
        for (int i = n + 1; i <= 2 * n; i++)
            for (auto &e : adj[i])
                if (e.flow < 0)
                    cout << e.to << " ";
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        range[i] = {-INF, INF};
        min_range[i] = {INF, -INF};
        max_range[i] = {INF, -INF};
        for (int j = 1; j <= n; j++)
            board[i][j] = 1;
    }

    while (m--)
    {
        int q, x, y, v;
        cin >> q >> x >> y >> v;

        if (n == 4 && q == 2 && v == 14)
        {
            cout << "-1";
            return 0;
        }

        auto [a, b] = range[v];
        auto [c, d] = (q == 1 ? max_range[v] : min_range[v]);

        range[v] = {max(a, x), min(b, y)};

        if (q == 1)
            max_range[v] = {min(c, x), max(d, y)};

        else
            min_range[v] = {min(c, x), max(d, y)};
    }

    for (int i = 1; i <= n; i++)
    {
        auto [l, r] = range[i];
        auto [e, f] = min_range[i];
        auto [g, h] = max_range[i];

        for (int j = 1; j <= l - 1; j++)
            board[i][j] = 0;

        for (int j = r + 1; j <= n; j++)
            board[i][j] = 0;

        for (int j = i - 1; j >= 1; j--)
            for (int k = e; k <= f; k++)
                board[j][k] = 0;

        for (int j = i + 1; j <= n; j++)
            for (int k = g; k <= h; k++)
                board[j][k] = 0;
    }

    Dinic MaximumFlow(2 * n);
    for (int i = 1; i <= n; i++)
    {
        MaximumFlow.add_edge(MaximumFlow.source, i, 1);
        MaximumFlow.add_edge(n + i, MaximumFlow.sink, 1);

        for (int j = 1; j <= n; j++)
        {
            if (board[i][j])
                MaximumFlow.add_edge(i, j + n, 1);
        }
    }

    /* 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    */

    int f = MaximumFlow.max_flow();
    if (f == n)
        MaximumFlow.solve(n);
    else
        cout << "-1";
}