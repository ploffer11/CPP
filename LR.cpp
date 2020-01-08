#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef tuple<int, int, int> t;
const int INF = 0x3f3f3f3f;

struct MinCostMaxFlow
{
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
        adj[to].back().rev = adj[to].size() - 1;
    }

    pii mcmf()
    {
        int cost = 0, flow = 0;
        while (1)
        {
            fill(prev.begin(), prev.end(), pii(-1, -1));
            fill(dis.begin(), dis.end(), INF);

            queue<int> q;
            in_queue[source] = true;
            dis[source] = 0;
            q.push(source);

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

int AL[300], AR[300];
int BL[300], BR[300];

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    MinCostMaxFlow MCMF(n + m);

    for (int i = 1; i <= n; i++)
        cin >> AL[i];
    for (int i = 1; i <= n; i++)
        cin >> AR[i];
    for (int i = 1; i <= m; i++)
        cin >> BL[i];
    for (int i = 1; i <= m; i++)
        cin >> BR[i];

    vector<pii> edge;
    while (k--)
    {
        int u, v;
        cin >> u >> v;
        MCMF.add_edge(u, n + v, 1, 0);
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += AL[i];
        MCMF.add_edge(MCMF.source, i, AL[i], -1);
        MCMF.add_edge(MCMF.source, i, AR[i] - AL[i], 0);
    }

    for (int i = 1; i <= m; i++)
    {
        sum += BL[i];
        MCMF.add_edge(n + i, MCMF.sink, BL[i], -1);
        MCMF.add_edge(n + i, MCMF.sink, BR[i] - BL[i], 0);
    }

    pii x = MCMF.mcmf();
    int cost = x.first, flow = x.second;

    if (-cost != sum)
    {
        cout << "-1";
        return 0;
    }

    else
    {
        cout << flow << "\n";
    }
}
