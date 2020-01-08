#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

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
};

int n, m;
int dis[505][505];
vector<int> black1, black2, white1;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        memset(dis, 0x3f, sizeof(dis));
        black1.clear();
        black2.clear();

        cin >> n >> m;
        MinCostMaxFlow MCMF(2 * n);

        while (m--)
        {
            int u, v;
            cin >> u >> v;
            dis[u][v] = dis[v][u] = 1;
        }

        for (int i = 1; i <= 2 * n; i++)
        {
            int x;
            cin >> x;
            if (x)
                (i <= n ? black1 : black2).push_back((i <= n ? i : i - n));
            if (i <= n)
                dis[i][i] = 0;
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

        for (auto i : black1)
            MCMF.add_edge(MCMF.source, i, 1, 0);

        for (auto i : black2)
            MCMF.add_edge(i + n, MCMF.sink, 1, 0);

        for (auto i : black1)
        {
            for (auto j : black2)
            {
                //cout << i << " -> " << j << " : " << dis[i][j] << "\n";
                MCMF.add_edge(i, j + n, 1, dis[i][j]);
            }
        }

        auto [cost, flow] = MCMF.mcmf();
        cout << cost << "\n";
    }
}