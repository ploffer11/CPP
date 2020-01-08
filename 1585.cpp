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

    MinCostMaxFlow(int n, int m)
    {
        source = 0;
        sink = n + m + 1;

        adj.resize(sink + 1);
        prev.resize(sink + 1, pii(-1, -1));
        dis.resize(sink + 1, INF);
        in_queue.resize(sink + 1, false);

        for (int i = 1; i <= n; i++)
            add_edge(source, i, 1, 0);

        for (int i = n + 1; i <= n + m; i++)
            add_edge(i, sink, 1, 0);
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
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, t, f;
    cin >> n;
    vector<int> S(n), E(n);
    for (int i = 0; i < n; i++)
        cin >> S[i];
    for (int i = 0; i < n; i++)
        cin >> E[i];

    cin >> t >> f;

    sort(S.begin(), S.end());
    sort(E.begin(), E.end());

    for (int q = 1; q <= 2; q++)
    {
        MinCostMaxFlow MCMF(n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int time = E[j] - S[i];

                if (1 <= time && time <= t)
                {
                    int cost = min((t - time) * (t - time), f);
                    MCMF.add_edge(i + 1, j + n + 1, 1, (q == 1 ? cost : -cost));
                }

                else if (1 <= time)
                    MCMF.add_edge(i + 1, j + n + 1, 1, 0);
            }
        }
        auto [cost, flow] = MCMF.mcmf();
        if (flow == n)
        {
            cout << (q == 1 ? cost : -cost) << ' ';
        }
        else
        {
            cout << -1;
            return 0;
        }
    }
}