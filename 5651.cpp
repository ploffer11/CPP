#include <bits/stdc++.h>
using namespace std;

class Dinic
{
private:
    struct Edge
    {
        int to, flow, cap, rev;
        Edge(int t, int c) : to(t), cap(c), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<vector<int>> floyd;
    vector<int> work, depth;
    int source, sink, n;

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

    int max_flow()
    {
        int flow = 0;
        while (1)
        {
            bfs();

            if (depth[sink] == -1)
                return flow;

            fill(work.begin(), work.end(), 0);
            while (1)
            {
                int f = dfs(source, 987654321);
                if (f < 0)
                    break;
                flow += f;
            }
        }
    }

    void fill_floyd()
    {
        int s = 0;
        for (auto &vt : adj)
        {
            for (auto &e : vt)
            {
                if (e.cap - e.flow > 0)
                    floyd[s][e.to] = 1;
            }
            s++;
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    floyd[i][j] |= floyd[i][k] & floyd[k][j];
    }

    bool can_move(int u, int v)
    {
        if (floyd[u][v])
            return true;

        for (int i = 1; i <= n; i++)
        {
            if (floyd[u][i] && floyd[i][v])
                return true;
        }

        return false;
    }

public:
    Dinic(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        floyd.resize(n + 1);
        work.resize(n + 1);
        depth.resize(n + 1);

        for (int i = 1; i <= n; i++)
            floyd[i].resize(n + 1, 0);

        source = 1;
        sink = n;
    }

    void add_edge(int u, int v, int cap)
    {
        adj[u].push_back(Edge(v, cap));
        adj[v].push_back(Edge(u, 0));

        adj[u].back().rev = adj[v].size() - 1;
        adj[v].back().rev = adj[u].size() - 1;
    }

    void solve()
    {
        //cout << "max flow: " << max_flow() << endl;
        max_flow();
        fill_floyd();
        int ans = 0;

        int s = 0;
        for (auto &vt : adj)
        {
            for (auto &e : vt)
            {
                //cout << "s e.to e.flow e.cap: " << s << " " << e.to << " " << e.flow << " " << e.cap << endl;
                if (e.flow > 0 && e.flow == e.cap && !can_move(s, e.to))
                {
                    ans++;
                }
            }
            s++;
        }

        cout << ans << '\n';
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        Dinic NetworkFlow(n);

        while (m--)
        {
            int u, v, c;
            cin >> u >> v >> c;
            NetworkFlow.add_edge(u, v, c);
        }

        NetworkFlow.solve();
    }
}