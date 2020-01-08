#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class MinCostMaxFlow
{
private:
    struct Edge
    {
        ld cost;
        int to, flow, cap, rev;
        Edge(int to, int cap, ld cost)
            : to(to), cap(cap), cost(cost), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<pii> prev;
    vector<ld> dis;
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
    }

    void add_edge(int from, int to, int cap, ld cost)
    {
        adj[from].push_back(Edge(to, cap, cost));
        adj[to].push_back(Edge(from, 0, -cost));
        adj[from].back().rev = adj[to].size() - 1;
        adj[to].back().rev = adj[from].size() - 1;
    }

    pair<ld, int> mcmf()
    {
        ld cost = 0;
        int flow = 0;
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
        return {cost, flow};
    }

    void solve(int n, int m)
    {
        for (int i = 1; i <= n; i++)
        {
            for (auto &e : adj[i])
            {
                if (n + 1 <= e.to && e.to <= n + m)
                {
                    cout << e.flow;
                }
            }
            cout << '\n';
        }
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m, f = 0;
    cin >> n >> m;

    MinCostMaxFlow MCMF(n, m);

    ld c = 0.0000000000000000000000000001;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        f += x;
        MCMF.add_edge(MCMF.source, i, x, 0);
        for (int j = n + 1; j <= n + m; j++)
        {
            MCMF.add_edge(i, j, 1, c *= 2);
        }
    }

    for (int i = n + 1; i <= n + m; i++)
    {
        int x;
        cin >> x;
        MCMF.add_edge(i, MCMF.sink, x, 0);
    }

    auto [cost, flow] = MCMF.mcmf();

    //cout << cost << "\n";
    if (flow != f)
    {
        cout << -1;
        return 0;
    }
    else
    {
        MCMF.solve(n, m);
    }
}