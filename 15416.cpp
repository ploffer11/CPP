#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

struct FastMinCostMaxFlow
{
    struct Edge
    {
        int pos, cap, rev, cost;
    };

    int source, sink, sz;

    FastMinCostMaxFlow(int n)
        : ptr(n + 2), phi(n + 2), inque(n + 2), dis(n + 2), visit(n + 2), sz(n + 2), adj(n + 2)
    {
        source = 0;
        sink = n + 1;
    }

    vector<int> ptr, phi, inque, dis;
    vector<bool> visit;
    vector<vector<Edge>> adj;

    void add_edge(int u, int v, int cap, int cost)
    {
        adj[u].push_back({v, cap, (int)adj[v].size(), cost});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1, -cost});
    }

    void prep(int source, int sink)
    {
        fill(phi.begin(), phi.end(), INF);
        fill(dis.begin(), dis.end(), INF);
        queue<int> q;
        q.push(source);
        inque[source] = 1;
        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inque[s] = 0;
            for (auto &e : adj[s])
            {
                if (e.cap > 0 && phi[e.pos] > phi[s] + e.cost)
                {
                    phi[e.pos] = phi[s] + e.cost;
                    if (!inque[e.pos])
                    {
                        inque[e.pos] = 1;
                        q.push(e.pos);
                    }
                }
            }
        }

        for (int i = 0; i < sz; i++)
            for (auto &j : adj[i])
                if (j.cap > 0)
                    j.cost += phi[i] - phi[j.pos];

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push(pii(0, source));
        dis[source] = 0;
        while (!pq.empty())
        {
            auto l = pq.top();
            pq.pop();
            if (dis[l.second] != l.first)
                continue;
            for (auto &i : adj[l.second])
            {
                if (i.cap > 0 && dis[i.pos] > l.first + i.cost)
                {
                    dis[i.pos] = l.first + i.cost;
                    pq.push(pii(dis[i.pos], i.pos));
                }
            }
        }
    }
    int dfs(int pos, int sink, int flow)
    {
        visit[pos] = 1;

        if (pos == sink)
            return flow;

        for (; ptr[pos] < adj[pos].size(); ptr[pos]++)
        {
            auto &i = adj[pos][ptr[pos]];
            if (!visit[i.pos] && dis[i.pos] == i.cost + dis[pos] && i.cap > 0)
            {
                int ret = dfs(i.pos, sink, min(i.cap, flow));
                if (ret != 0)
                {
                    i.cap -= ret;
                    adj[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    pii mcmf()
    {
        prep(source, sink);
        for (int i = 0; i < sz; i++)
            dis[i] += phi[sink] - phi[source];
        int cost = 0, flow = 0;

        while (true)
        {
            fill(ptr.begin(), ptr.end(), 0);
            fill(visit.begin(), visit.end(), 0);

            int tmp = 0;
            while ((tmp = dfs(source, sink, 1e9)))
            {
                cost += dis[sink] * tmp;
                flow += tmp;
                fill(visit.begin(), visit.end(), 0);
            }

            tmp = 1e9;
            for (int i = 0; i < sz; i++)
            {
                if (!visit[i])
                    continue;
                for (auto &j : adj[i])
                    if (j.cap > 0 && !visit[j.pos])
                        tmp = min(tmp, (dis[i] + j.cost) - dis[j.pos]);
            }

            if (tmp > 1e9 - 200)
                break;

            for (int i = 0; i < sz; i++)
                if (!visit[i])
                    dis[i] += tmp;
        }
        return {cost, flow};
    }
};

int d(pii &a, pii &b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pii> bottle, courier;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        bottle.push_back({x, y});
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        courier.push_back({x, y});
    }

    int x, y;
    cin >> x >> y;

    pii g = {x, y};

    FastMinCostMaxFlow MCMF(n + m + 1);

    ll ans = 0;
    int diff = INF;
    for (int i = 1; i <= m; i++)
    {
        MCMF.add_edge(MCMF.source, i, 1, 0);
        for (int j = m + 1; j <= m + n; j++)
        {
            auto &c = courier[i - 1];
            auto &b = bottle[j - m - 1];

            MCMF.add_edge(i, j, 1, d(c, b));
            diff = min(diff, d(c, b) - d(b, g));
        }
    }

    MCMF.add_edge(MCMF.source, m + n + 1, n, 0);
    for (int i = m + 1; i <= m + n; i++)
    {
        auto &b = bottle[i - m - 1];
        MCMF.add_edge(m + n + 1, i, 1, d(b, g));
        MCMF.add_edge(i, MCMF.sink, 1, 0);
        ans += d(b, g);
    }

    auto [cost, flow] = MCMF.mcmf();
    ans += cost;

    if (MCMF.invalid(m + n + 1))
        cout << ans + diff;
    else
        cout << ans;
}