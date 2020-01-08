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

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
char board[505][505];
int white_cnt[505][505];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {

        int n, m, cnt = 0;
        cin >> n >> m;

        vector<pii> black, white;
        //map<pii, int> white_cnt;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> board[i][j];
                if (board[i][j] == 'B')
                    black.push_back({i, j});
                else if (board[i][j] == 'W')
                {
                    white.push_back({i, j});
                    white_cnt[i][j] = ++cnt;
                }
            }
        }

        if (black.size() * 2 != white.size())
        {
            cout << "NO\n";
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                    board[i][j] = 0;
            continue;
        }

        Dinic even(white.size() + black.size()), odd(white.size() + black.size());

        for (int i = 1; i <= black.size(); i++)
        {
            even.add_edge(even.source, i, 1);
            odd.add_edge(odd.source, i, 1);
        }

        for (int i = black.size() + 1; i <= black.size() + white.size(); i++)
        {
            even.add_edge(i, even.sink, 1);
            odd.add_edge(i, odd.sink, 1);
        }

        int cnt2 = 1;
        for (auto [r, c] : black)
        {
            for (int k = 0; k < 4; k++)
            {
                int R = r + dr[k], C = c + dc[k];
                if (board[R][C] == 'W')
                {
                    //cout << r << " " << c << " " << R << " " << C << '\n';
                    (R % 2 == 0 ? even : odd).add_edge(cnt2, white_cnt[R][C] + black.size(), 1);
                }
            }
            cnt2++;
        }

        //cout << even.max_flow() << " " << odd.max_flow() << '\n';
        if (even.max_flow() == black.size() && odd.max_flow() == black.size())
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                board[i][j] = 0;
    }
}