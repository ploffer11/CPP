#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

class EdmondsKarp
{
private:
    struct Edge
    {
        int to, cap, flow, rev;
        Edge(int t, int c) : to(t), cap(c), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<pii> via;

    int source, sink;

public:
    EdmondsKarp(int n, int m)
    {
        source = 0;
        sink = n + m + 1;

        adj.resize(sink + 1);
        via.resize(sink + 1);

        for (int i = 1; i <= n; i++)
            add_edge(source, i, 2);

        for (int i = n + 1; i <= n + m; i++)
            add_edge(i, sink, 1);
    }

    void add_edge(int from, int to, int cap)
    {
        adj[from].push_back(Edge(to, cap));
        adj[to].push_back(Edge(from, 0));

        adj[from].back().rev = adj[to].size() - 1;
        adj[to].back().rev = adj[from].size() - 1;
    }

    int max_flow()
    {
        int flow = 0;

        while (1)
        {
            fill(via.begin(), via.end(), pii(-1, -1));
            queue<int> q;
            q.push(source);

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                bool flag = false;

                for (int i = 0; i < adj[node].size(); i++)
                {
                    auto &e = adj[node][i];
                    if (via[e.to] == pii(-1, -1) && e.cap - e.flow > 0)
                    {
                        q.push(e.to);
                        via[e.to] = {node, i};

                        if (e.to == sink)
                        {
                            flag = true;
                            break;
                        }
                    }
                }

                if (flag)
                    break;
            }

            if (via[sink] == pii(-1, -1))
                break;

            int f = 987654321;
            for (int i = sink; i != source; i = via[i].first)
            {
                auto [prev_node, e_idx] = via[i];
                f = min(adj[prev_node][e_idx].cap - adj[prev_node][e_idx].flow, f);
            }

            for (int i = sink; i != source; i = via[i].first)
            {
                auto [prev_node, e_idx] = via[i];
                auto &e = adj[prev_node][e_idx];

                e.flow += f;
                adj[e.to][e.rev].flow -= f;
            }

            flow += f;
        }
        return flow;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    EdmondsKarp NetworkFlow(n, m);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        while (x--)
        {
            int y;
            cin >> y;
            NetworkFlow.add_edge(i, n + y, 1);
        }
    }

    cout << NetworkFlow.max_flow();
}