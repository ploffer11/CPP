#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int INF = 987654321;
const int MOD = 1e9 + 7;
const int BLACK = 1;
const int WHITE = 2;

vector<pii> vt1, vt2;

string str_board[505][105][105];
int cnt;
int parent[10005];
int prev_board[105][105], after_board[105][105];
int idx_board[105][105];
int numbering[105][105];
int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
string dir = "DURL";
bool visit[105][105];

class MinCostMaxFlow
{
private:
    struct Edge
    {
        int to, flow, cap, cost, rev;
        Edge(int to, int cap, int cost)
            : to(to), cap(cap), cost(cost), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<pii> prev;
    vector<int> dis;
    vector<bool> in_queue;

public:
    int source, sink, fake_source;

    MinCostMaxFlow(int n)
    {
        source = 0;
        sink = n + 1;

        adj.resize(sink + 1);
        prev.resize(sink + 1, pii(-1, -1));
        dis.resize(sink + 1, INF);
        in_queue.resize(sink + 1, false);
    }

    void add_edge(int from, int to, int cap, int cost)
    {
        adj[from].push_back(Edge(to, cap, cost));
        adj[to].push_back(Edge(from, 0, -cost));
        adj[from].back().rev = adj[to].size() - 1;
        adj[to].back().rev = adj[from].size() - 1;
    }

    pii mcmf()
    {
        int cost = 0, flow = 0;
        while (1)
        {
            fill(prev.begin(), prev.end(), pii(-1, -1));
            fill(dis.begin(), dis.end(), INF);

            queue<int> q;
            q.push(source);
            in_queue[source] = true;
            dis[source] = 0;

            while (!q.empty())
            {
                int s = q.front();
                q.pop();
                in_queue[s] = false;

                for (int i = 0; i < adj[s].size(); i++)
                {
                    auto &e = adj[s][i];
                    if (dis[e.to] > dis[s] + e.cost && e.cap - e.flow > 0)
                    {
                        dis[e.to] = dis[s] + e.cost;
                        prev[e.to] = {s, i};

                        if (!in_queue[e.to])
                        {
                            in_queue[e.to] = true;
                            q.push(e.to);
                        }
                    }
                }
            }

            if (dis[sink] == INF)
                break;

            int f = INF;

            for (int i = sink; i != source; i = prev[i].first)
            {
                auto &e = adj[prev[i].first][prev[i].second];
                f = min(f, e.cap - e.flow);
            }

            for (int i = sink; i != source; i = prev[i].first)
            {
                auto &e = adj[prev[i].first][prev[i].second];
                e.flow += f;
                adj[e.to][e.rev].flow -= f;
                cost += e.cost * f;
            }

            flow += f;
        }

        return pii(cost, flow);
    }

    void match()
    {
        using tt = tuple<int, int, int, int, int, int, int>;
        queue<tt> q;

        int sz = (sink - 1) / 2;

        for (int i = 1; i <= sz; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                auto &e = adj[i][j];
                if (e.cap > 0 && e.flow > 0)
                {
                    //cout << i << " " << e.cap << " " << e.cost << " " << e.flow << "\n";
                    //cout << "??: " << e.to << '\n';
                    auto [r1, c1] = vt1[i - 1];
                    auto [r2, c2] = vt2[e.to - sz - 1];
                    //printf("match: (%d, %d) -> (%d, %d)\n", r1, c1, r2, c2);
                    //cout << str_board[i - 1][r2][c2] << endl;

                    int r = r1, c = c1;
                    for (auto d : str_board[i - 1][r2][c2])
                    {
                        int dir, X, Y, Z;
                        if (d == 'D')
                            dir = 0, X = 1, Y = c, Z = r;

                        else if (d == 'U')
                            dir = 1, X = 1, Y = c, Z = r - 1;

                        else if (d == 'R')
                            dir = 2, X = 0, Y = r, Z = c;

                        else if (d == 'L')
                            dir = 3, X = 0, Y = r, Z = c - 1;

                        int R = r + dr[dir], C = c + dc[dir];
                        q.push({r, c, R, C, X, Y, Z});
                        r = R, c = C;
                    }

                    break;
                }
            }
        }

        while (!q.empty())
        {
            auto [r, c, R, C, X, Y, Z] = q.front();
            q.pop();

            if (prev_board[r][c] == BLACK && prev_board[R][C] == WHITE)
            {
                swap(prev_board[r][c], prev_board[R][C]);
                //cout << r << " " << c << " -> " << R << " " << C << '\n';
                cout << X << " " << Y << " " << Z << '\n';
            }

            else
            {
                q.push({r, c, R, C, X, Y, Z});
            }
        }
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    int u, v;
    cin >> n >> m >> u >> v;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            numbering[i][j] = (i - 1) * n + j;

    int a, b;
    while (u--)
    {
        cin >> a >> b;
        prev_board[a][b] = BLACK;
    }

    while (v--)
    {
        cin >> a >> b;
        prev_board[a][b] = WHITE;
    }
    cin >> u >> v;
    while (u--)
    {
        cin >> a >> b;
        after_board[a][b] = BLACK;
    }
    while (v--)
    {
        cin >> a >> b;
        after_board[a][b] = WHITE;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            //cout << prev_board[i][j] << " < - > " << after_board[i][j] << '\n';
            if ((!prev_board[i][j] && after_board[i][j]) || (!after_board[i][j] && prev_board[i][j]))
            {
                cout << "-1";
                return 0;
            }

            if ((i + j) % 2 == 0)
            {
                prev_board[i][j] = (prev_board[i][j] == 0 ? 0 : 3 - prev_board[i][j]);
                after_board[i][j] = (after_board[i][j] == 0 ? 0 : 3 - after_board[i][j]);
            }

            if (prev_board[i][j] == BLACK)
                vt1.push_back({i, j});

            if (after_board[i][j] == BLACK)
            {
                vt2.push_back({i, j});
                idx_board[i][j] = cnt++;
            }
        }
    }

    if (vt1.size() != vt2.size())
    {
        cout << "-1";
        return 0;
    }

    int sz = vt1.size();
    MinCostMaxFlow MCMF(2 * sz);

    for (int i = 1; i <= sz; i++)
        MCMF.add_edge(MCMF.source, i, 1, 0);

    for (int i = sz + 1; i <= sz + sz; i++)
        MCMF.add_edge(i, MCMF.sink, 1, 0);

    for (int i = 0; i < vt1.size(); i++)
    {
        auto [r1, c1] = vt1[i];
        memset(visit, 0, sizeof(visit));

        using tt = tuple<int, int, int, string>;
        queue<tt> q;

        q.push({0, r1, c1, ""});
        visit[r1][c1] = true;

        while (!q.empty())
        {
            auto [depth, r, c, str] = q.front();
            q.pop();

            if (after_board[r][c] == BLACK)
            {
                //cout << i << " <- " << depth << " " << r << " " << c << " " << str << " " << idx_board[r][c] << "\n";
                //cout << "add edge: " << i + 1 << " -> " << sz + idx_board[r][c] + 1 << '\n';
                str_board[i][r][c] = str;
                MCMF.add_edge(i + 1, sz + idx_board[r][c] + 1, 1, depth);
            }

            for (int i = 0; i < 4; i++)
            {
                int R = r + dr[i], C = c + dc[i];
                if (after_board[R][C] && !visit[R][C])
                {
                    visit[R][C] = true;
                    q.push({depth + 1, R, C, str + dir[i]});
                }
            }
        }
    }

    auto [cost, flow] = MCMF.mcmf();
    //cout << cost << ' ' << flow << '\n';

    if (flow != sz)
    {
        cout << "-1";
        return 0;
    }

    cout << cost << '\n';
    MCMF.match();
}