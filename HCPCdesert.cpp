#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dp[100'005][11];
ll dessert[100'005][11];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            cin >> dessert[i][j];
    for (int i = 1; i <= m; i++)
        dp[1][i] = dessert[1][i];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ll x = -1;
            for (int k = 1; k <= m; k++)
            {
                x = max(x, dp[i - 1][k] + (j == k ? dessert[i][j] / 2 : dessert[i][j]));
            }
            dp[i][j] = x;
        }
    }

    ll ans = -1;
    for (int i = 1; i <= m; i++)
        ans = max(ans, dp[n][i]);
    cout << ans;
}