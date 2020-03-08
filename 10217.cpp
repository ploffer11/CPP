#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<ll>> dis(n + 1, vector<ll>(m + 1, INF));
        vector<vector<bool>> finish(n + 1, vector<bool>(m + 1, 0));
        using tt = tuple<ll, ll, ll>;
        vector<vector<tt>> adj(n + 1, vector<tt>());

        while (m--)
        {
            int u, v, c, d;
            cin >> u >> v >> c >> d;
            adj[u].push_back({v, c, d});
        }
        priority_queue<tt, vector<tt>, greater<tt>> pq;
        dis[1][0] = 0;
        pq.push({0, 1, 0});
        while (!pq.empty())
        {
            auto [time, s, cost] = pq.top();

            for (auto [e, c, t] : adj[s])
            {
            }
        }
    }
}