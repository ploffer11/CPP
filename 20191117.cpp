#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dp[85][100005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x11, sizeof(dp));

    vector<pii> vt;
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int x, s;
        cin >> x >> s;
        vt.push_back({max(1, x - s), min(m, x + s)});
    }

    sort(vt.begin(), vt.end());

    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = 0;
        auto [l, r] = vt[i - 1];

        for (int j = 0; j <= m; j++)
        {
            int k = min(r + j, m);
            int q = max(0, l - j - 1);
            dp[i][k] = min(dp[i][k], min(dp[i - 1][k], dp[i - 1][q] + j));
        }
        for (int j = m; j >= 0; j--)
        {
            dp[i][j] = min(dp[i][j], dp[i][j + 1]);
        }

        for (int j = 1; j <= m; j++)
            dp[i + 1][j] = dp[i][j];
    }
    cout << dp[n][m];
}