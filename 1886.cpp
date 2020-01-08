#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;
const int INF = 987654321;

int visit[15][15], board[15][15];
int n, m;
int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
vector<pii> prisoner;
map<pii, int> door;
vector<t> edges;

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

    Dinic(int n, int m, int t)
    {
        source = 0;
        sink = n + t * m + 1;
        adj.resize(sink + 1);
        depth.resize(sink + 1);
        work.resize(sink + 1);

        for (int i = 1; i <= n; i++)
            add_edge(source, i, 1);

        for (int i = n + 1; i <= n + t * m; i++)
            add_edge(i, sink, 1);

        for (auto [person, door, time] : edges)
        {
            for (int i = time; i <= t; i++)
            {
                int j = n + (i - 1) * m + door;
                add_edge(person, j, 1);
            }
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

bool check(int r, int c)
{
    return (0 <= r && r < n && 0 <= c && c < m);
}

void connect()
{
    int cnt = 0;
    for (int k = 0; k < prisoner.size(); k++)
    {
        auto [r, c] = prisoner[k];
        memset(visit, 0, sizeof(visit));
        visit[r][c] = 1;
        queue<pii> q;
        q.push({r, c});

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int R = r + dr[i], C = c + dc[i];
                if (check(R, C) && !board[R][C] && !visit[R][C])
                {
                    if (door[{R, C}])
                    {
                        edges.push_back({k + 1, door[{R, C}], visit[r][c]});
                        continue;
                    }
                    q.push({R, C});
                    visit[R][C] = visit[r][c] + 1;
                }
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char x;
            cin >> x;
            if (x == 'D')
                door[{i, j}] = ++cnt;
            else if (x == '.')
                prisoner.push_back({i, j});
            else
                board[i][j] = 1;
        }
    }

    connect();

    int param = 200;
    int s = 1, e = param;

    while (s <= e)
    {
        int m = (s + e) / 2;
        Dinic MaximumFlow(prisoner.size(), cnt, m);

        int f = MaximumFlow.max_flow();

        if (f == prisoner.size())
            e = m - 1;
        else
            s = m + 1;
    }

    if (s >= param)
        cout << "impossible";
    else
        cout << s;
}
