#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;
const int MAX = 100'005;

vector<pii> adj[MAX];
ll dis[MAX];
bool valid[MAX];
bool finish[MAX];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n - 1; i++)
        cin >> valid[i];
    valid[n - 1] = 0;

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (!valid[u] && !valid[v])
        {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    for (int i = 0; i <= n; i++)
        dis[i] = INF;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dis[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        //cout << "node: " << s << " dis[s]: " << cur << '\n';

        if (finish[s])
            continue;

        for (auto [e, w] : adj[s])
        {
            if (dis[e] > dis[s] + w)
            {
                dis[e] = dis[s] + w;
                pq.push({dis[e], e});
            }
        }

        finish[s] = true;
    }

    cout << (dis[n - 1] == INF ? -1 : dis[n - 1]);
}
