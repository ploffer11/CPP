#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
#define int ll
using pii = pair<int, int>;
const ll INF = (ll)1 << 60;
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
                int f = dfs(source, INF);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }

    void solve(int n)
    {
        max_flow();

        fill(depth.begin(), depth.end(), -1);

        vector<int> ans;
        queue<int> q;
        q.push(source);
        depth[source] = 0;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();

            bool flag = true;
            for (auto &e : adj[s])
            {
                if (e.cap > 0 && e.cap - e.flow > 0 && depth[e.to] == -1)
                {
                    depth[e.to] = depth[s] + 1;
                    q.push(e.to);
                    flag = false;
                }
            }

            if (flag && 1 <= s && s <= n)
            {
                bool flag2 = false;
                for (auto &e : adj[s])
                {
                    if (e.to == s + n && e.cap == e.flow)
                        flag2 = true;
                }
                if (flag2)
                    ans.push_back(s);
            }
        }

        sort(ans.begin(), ans.end());
        for (auto i : ans)
            cout << i << ' ';
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, s, e;
    cin >> n >> m >> s >> e;

    Dinic MF(2 * n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        MF.add_edge(i, n + i, x);
    }

    MF.add_edge(MF.source, s, INF);
    MF.add_edge(n + e, MF.sink, INF);

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        MF.add_edge(n + a, b, INF);
        MF.add_edge(n + b, a, INF);
    }

    MF.solve(n);
}