#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

class Dijkstra
{
private:
    vector<vector<pair<int, ll>>> adj;
    vector<ll> dis;
    vector<int> via;
    vector<bool> finish;

public:
    Dijkstra(int n) : dis(n + 1), finish(n + 1), adj(n + 1), via(n + 1) {}
    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
        fill(finish.begin(), finish.end(), false);

        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0, s});
        dis[s] = 0;

        while (!pq.empty())
        {
            auto [cur, s] = pq.top();
            pq.pop();

            if (finish[s])
                continue;
            finish[s] = true;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    via[e] = s;
                    dis[e] = dis[s] + w;
                    pq.push({dis[e], e});
                }
            }
        }
        return dis[e];
    }
};

class SPFA
{
private:
    int n;
    vector<bool> inq;
    vector<int> cycle, via;
    vector<ll> dis;
    vector<vector<pair<int, ll>>> adj;

public:
    SPFA(int n) : dis(n + 1), inq(n + 1), adj(n + 1), cycle(n + 1), via(n + 1), n(n) {}

    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
        fill(cycle.begin(), cycle.end(), 0);

        queue<int> q;
        dis[s] = 0;
        q.push(s);
        inq[s] = true;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inq[s] = false;
            cycle[s]++;

            if (cycle[s] == n)
                continue;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    via[e] = s;
                    if (!inq[e])
                    {
                        q.push(e);
                        inq[e] = true;
                    }
                }
            }
        }
        return dis[e];
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int, int>> edge;

    while (m--)
    {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        edge.push_back({u, v, c, f});
    }

    ll ans = 0;
    for (int i = 1; i <= 1000; i++)
    {
        SPFA graph(n);
        for (auto [u, v, c, f] : edge)
        {
            if (f >= i)
            {
                graph.add_edge(u, v, c);
                graph.add_edge(v, u, c);
            }
        }
        ll q = graph.query(1, n);

        if (q == INF)
            continue;

        ans = max(ans, (i * 1000000) / q);
    }
    cout << ans;
}