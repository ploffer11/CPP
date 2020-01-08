#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dp[250'005];
ll w[300], t[300];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x3f, sizeof(dp));

    int n, W;
    cin >> n >> W;

    for (int i = 1; i <= n; i++)
        cin >> w[i] >> t[i];

    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 250000; j - t[i] >= 0; j--)
        {
            dp[j] = min(dp[j], dp[j - t[i]] + w[i]);
        }
    }

    ll ans = -1;
    for (int i = 1; i <= 250000; i++)
    {

        if (dp[i] < W)
            continue;

        if (i * 1000 / dp[i] != 0)
            cout << i << " " << i * 1000 / dp[i] << "\n";
        ans = max(ans, i * 1000 / dp[i]);
    }

    cout << ans;
}