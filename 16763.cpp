#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dis[2][50005];
bool finish[2][50005];
vector<pii> hay, adj[50005];

void dijk(int i, int s)
{
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto [cur, node] = pq.top();
        pq.pop();

        if (finish[i][node])
            continue;

        for (auto [e, cost] : adj[node])
        {
            if (dis[i][e] > cur + cost)
            {
                dis[i][e] = cur + cost;
                pq.push({dis[i][e], e});
            }
        }

        finish[i][node] = true;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));

    int n, m, k;
    cin >> n >> m >> k;

    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        hay.push_back({x, y});
    }

    dijk(0, n);

    for (auto [x, y] : hay)
    {
        adj[n + 1].push_back({x, dis[0][x] - y});
    }

    dijk(1, n + 1);

    for (int i = 1; i <= n - 1; i++)
    {
        cout << (dis[0][i] >= dis[1][i] ? "1\n" : "0\n");
    }
}