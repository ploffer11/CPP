#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

vector<tuple<int, int, int, int>> adj[1005];
vector<int> path;
bool finish[1005];
int dis[1005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));
    int n, m;
    int a, b, k, g;
    cin >> n >> m >> a >> b >> k >> g;

    for (int i = 0; i < g; i++)
    {
        int x;
        cin >> x;
        path.push_back(x);
    }

    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c, -1, -1});
        adj[v].push_back({u, c, -1, -1});
    }

    int cur = 0;
    for (int i = 0; i < g - 1; i++)
    {
        int s = path[i], e = path[i + 1];
        for (auto &edge : adj[s])
        {
            auto [a, b, c, d] = edge;
            if (a == e)
            {
                edge = {a, b, cur, cur + b - 1};
                break;
            }
        }

        s = path[i + 1], e = path[i];
        for (auto &edge : adj[s])
        {
            auto [a, b, c, d] = edge;
            if (a == e)
            {
                edge = {a, b, cur, cur + b - 1};
                cur += b;
                break;
            }
        }
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({k, a});
    dis[a] = k;

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        if (finish[s])
            continue;

        for (auto [e, cost, S, E] : adj[s])
        {
            if (S <= cur && cur <= E)
            {
                if (dis[e] > E + 1 + cost)
                {
                    dis[e] = E + 1 + cost;
                    pq.push({dis[e], e});
                }
            }
            else
            {
                if (dis[e] > cur + cost)
                {
                    dis[e] = cur + cost;
                    pq.push({dis[e], e});
                }
            }
        }
        finish[s] = true;
    }

    cout << dis[b] - k;
}