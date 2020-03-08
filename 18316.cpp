#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 1005;

ll dp[MAX][MAX];
ll M[MAX];
vector<pii> edge;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n, m, c;
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++)
        cin >> M[i];
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        edge.push_back({u, v});
    }

    dp[0][1] = 0;
    for (int t = 0; t <= 1001; t++)
    {
        for (auto [u, v] : edge)
        {
            if (dp[t][u] != -1)
            {
                dp[t + 1][v] = max(dp[t + 1][v], dp[t][u] + M[v]);
            }
        }
    }

    ll ans = 0;
    for (int t = 0; t <= 1001; t++)
    {
        ans = max(ans, dp[t][1] - c * t * t);
    }
    cout << ans;
}