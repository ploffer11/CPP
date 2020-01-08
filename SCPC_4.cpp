#include <bits/stdc++.h>
using namespace std;

int board[55][505];
vector<int> bomb[55][505];
int dr[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

class Dinic
{
private:
    struct Edge
    {
        int to, flow, capacity, reverse;
        Edge(int _to, int _capacity, int _reverse)
            : to(_to), capacity(_capacity), reverse(_reverse), flow(0)
        {
        }
    };

    vector<vector<Edge>> adj;
    vector<int> depth, start_idx;
    int n, source, sink;

    void bfs(int s)
    {
        start_idx.clear();
        depth.clear();

        start_idx.resize(sink + 1, 0);
        depth.resize(sink + 1, -1);

        depth[s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto &e : adj[node])
            {
                if (e.capacity - e.flow > 0 && depth[e.to] == -1)
                {
                    depth[e.to] = depth[node] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int s, int flow)
    {
        if (s == sink)
            return flow;

        for (int i = start_idx[s]; i < adj[s].size(); i++, start_idx[s]++)
        {
            auto &e = adj[s][i];

            if (depth[e.to] > depth[s] && e.capacity - e.flow > 0)
            {
                int f = dfs(e.to, min(flow, e.capacity - e.flow));
                if (f < 0)
                    continue;
                e.flow += f;
                adj[e.to][e.reverse].flow -= f;
                return f;
            }
        }

        return -1;
    }

public:
    Dinic(int r, int c, int cnt, int cap)
    {
        source = 0;
        sink = cnt + 2;

        int fake = cnt + 1;

        adj.resize(sink + 1);

        add_edge(source, fake, cap);

        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                int node = (i - 1) * r + j;
                add_edge(fake, node, 1);
                for (auto k : bomb[i][j])
                {
                    add_edge(node, k, 1);
                }
            }
        }

        for (int i = r * c + 1; i <= cnt; i++)
        {
            add_edge(i, sink, 1);
        }
    }

    void add_edge(int u, int v, int capacity)
    {
        adj[u].push_back(Edge(v, capacity, adj[v].size()));
        adj[v].push_back(Edge(u, 0, adj[u].size() - 1));
    }

    int max_flow()
    {
        int maximum_flow = 0;
        while (1)
        {
            bfs(source);
            if (depth[sink] < 0)
                return maximum_flow;

            while (1)
            {
                int f = dfs(source, 1987654321);

                if (f < 0)
                    break;

                maximum_flow += f;
            }
        }
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        int r, c;
        cin >> r >> c;

        int cnt = r * c;
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                scanf("%1d", &board[i][j]);
                if (board[i][j])
                    board[i][j] = ++cnt;
            }
        }

        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                for (int k = 0; k < 9; k++)
                {
                    int R = i + dr[k], C = j + dc[k];
                    if (board[R][C])
                        bomb[i][j].push_back(board[R][C]);
                }
            }
        }

        int s = 0, e = cnt - r * c;
        int total_bomb = cnt - r * c;
        
        while (s <= e)
        {
            int m = (s + e) / 2;
            Dinic NetworkFlow(r, c, cnt, m);

            int flow = NetworkFlow.max_flow();

            if (flow == total_bomb)
                e = m - 1;
            else
                s = m + 1;
        }

        cout << s << " " << e << endl;

        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                board[i][j] = 0;
                bomb[i][j].clear();
            }
        }
    }
}