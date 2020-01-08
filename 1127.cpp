#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
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
                int f = dfs(source, 987654321);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }
};

char partner[55][55];
vector<int> can_guard[55], already_guard[55], cant_guard[55];
bool check[55];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> partner[i][j];

    cin >> k;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        while (x--)
        {
            int y;
            cin >> y;
            already_guard[y + 1].push_back(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        while (x--)
        {
            int y;
            cin >> y;
            can_guard[y + 1].push_back(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= k; i++)
    {
        memset(check, 0, sizeof(check));
        Dinic MF(n);

        for (auto j : already_guard[i])
            check[j] = true;

        vector<int> can_guard_2;

        for (auto j : can_guard[i])
        {
            if (check[j])
                continue;
            check[j] = true;
            can_guard_2.push_back(j);
        }

        for (int j = 1; j <= n; j++)
            if (!check[j])
                cant_guard[i].push_back(j);

        for (auto j : already_guard[i])
            MF.add_edge(MF.source, j, INF);

        for (auto j : cant_guard[i])
            MF.add_edge(j, MF.sink, INF);

        for (auto j : already_guard[i])
            for (auto k : cant_guard[i])
                if (partner[j][k] == '1')
                    MF.add_edge(j, k, 1);

        for (auto j : already_guard[i])
            for (auto k : can_guard_2)
                if (partner[j][k] == '1')
                    MF.add_edge(j, k, 1);

        for (auto j : can_guard_2)
            for (auto k : cant_guard[i])
                if (partner[j][k] == '1')
                    MF.add_edge(j, k, 1);

        for (auto j : can_guard_2)
            for (auto k : can_guard_2)
                if (partner[j][k] == '1' && j != k)
                    MF.add_edge(j, k, 1);

        ans += MF.max_flow();
        //cout << ans << " ";
    }

    cout << ans;
}