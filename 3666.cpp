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
};

char board[105][105];
int army[105];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        vector<int> team, enemy;

        int n;
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> army[i];
        }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> board[i][j];

        for (int i = 1; i <= n; i++)
        {
            if (army[i] == 0)
                continue;

            int flag = true;
            for (int j = 1; j <= n; j++)
                if (board[i][j] == 'Y' && army[j] == 0)
                    flag = false;
            //cout << "edge: " << flag << " " << i << '\n';
            (flag ? team : enemy).push_back(i);
        }

        int s = 0, e = 100000;
        while (s <= e)
        {
            Dinic MF(2 * n);
            int m = (s + e) / 2;
            int f = m * enemy.size();

            for (auto i : team)
            {
                MF.add_edge(MF.source, i, army[i] - 1);
                MF.add_edge(i, n + i, army[i]);
            }

            for (auto i : enemy)
            {
                MF.add_edge(i, MF.sink, m);
                MF.add_edge(MF.source, i, army[i]);
                MF.add_edge(i, n + i, army[i]);
            }

            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (board[i][j] == 'Y')
                        MF.add_edge(n + i, j, INF);

            int flow = MF.max_flow();
            //cout << m << " " << f << " " << flow << '\n';
            if (flow == f)
                s = m + 1;
            else
                e = m - 1;
        }
        cout << e << '\n';
    }
}