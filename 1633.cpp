#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 987654321;

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
    int source, sink;

    MinCostMaximumFlow(int n, int m)
    {
        source = 0;
        int fake_source = n + m + 1;
        int white = n + m + 2;
        int black = m + n + 3;
        sink = n + m + 4;

        adj.resize(sink + 1);
        prev.resize(sink + 1, pii(-1, -1));
        dis.resize(sink + 1, INF);
        in_queue.resize(sink + 1, false);

        for (int i = 1; i <= n; i++)
            add_edge(fake_source, i, 1, 0);

        for (int i = n + 1; i <= n + n; i++)
            add_edge(i, black, 1, 0);

        for (int i = n + n + 1; i <= n + n + n; i++)
            add_edge(i, white, 1, 0);

        add_edge(source, fake_source, 30, 0);
        add_edge(white, sink, 15, 0);
        add_edge(black, sink, 15, 0);
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

    vector<pii> inp;

    int white, black;
    while (cin >> white >> black)
    {
        inp.push_back({white, black});
    }

    int n = inp.size();
    MinCostMaximumFlow MCMF(n, 2 * n);

    //cout << "n: " << n << endl;
    for (int i = 0; i < n; i++)
    {
        int p = i + 1;
        int w = p + n;
        int b = p + n + n;

        MCMF.add_edge(p, w, 1, -inp[i].first);
        MCMF.add_edge(p, b, 1, -inp[i].second);
        //cout << p << " " << w << " " << b << endl;
    }

    //cout << "Lets Go!!" << endl;
    auto [cost, flow] = MCMF.mcmf();
    //cout << "YEAHHH!!" << endl;
    //cout << flow << endl;
    cout << -cost;
}