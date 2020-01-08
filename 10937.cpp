#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 987654321;

int board[20][20], num[20][20];
int price[4][4] = {
    {100, 70, 40, 0},
    {70, 50, 30, 0},
    {40, 30, 20, 0},
    {0, 0, 0, 0},
};

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

class MinCostMaximumFlow
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

    MinCostMaximumFlow(int r, int c, int flow)
    {
        source = 0;
        fake_source = r * c + 1;
        sink = r * c + 2;

        adj.resize(sink + 1);
        prev.resize(sink + 1, pii(-1, -1));
        dis.resize(sink + 1, INF);
        in_queue.resize(sink + 1, false);

        add_edge(source, fake_source, flow, 0);
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
};

int main()
{
    int r, c;
    cin >> r;
    c = r;

    int cnt = 1;
    for (int i = 1; i <= r; i++)
    {
        string inp;
        cin >> inp;
        for (int j = 1; j <= c; j++)
        {
            if (inp[j - 1] != 'F')
                board[i][j] = inp[j - 1] - 'A';
            else
                board[i][j] = 3;

            num[i][j] = cnt++;
        }
    }

    int ans = 0;

    for (int f = 1; f <= (r * c) / 2; f++)
    {
        MinCostMaximumFlow MCMF(r, c, f);

        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                if ((i + j) % 2)
                {
                    MCMF.add_edge(MCMF.fake_source, num[i][j], 1, 0);

                    for (int k = 0; k < 4; k++)
                    {
                        int R = i + dr[k], C = j + dc[k];
                        if (1 <= R && R <= r && 1 <= C && C <= c)
                            MCMF.add_edge(num[i][j], num[R][C], 1, -price[board[i][j]][board[R][C]]);
                    }
                }
                else
                    MCMF.add_edge(num[i][j], MCMF.sink, 1, 0);
            }
        }
        auto [cost, flow] = MCMF.mcmf();
        ans = max(ans, -cost);

        //cout << f << " " << -cost << endl;
    }

    cout << ans;
}