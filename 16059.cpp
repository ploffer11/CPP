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

ll dp[300'005];
ll score[300'005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> score[i];

    for (int i = m + 1; i <= n; i++)
    {
        dp[i] += score[i];
        for (int j = i + m; j <= i + 2 * m - 1 && j <= n; j++)
            dp[j] = max(dp[j], dp[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    cout << ans;
}