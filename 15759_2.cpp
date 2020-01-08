#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;

ld dp[1005];
ll T[252], W[252];
ll n, w;

bool able(ld x)
{
    for (int i = 0; i <= w; i++)
        dp[i] = -INF;

    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        ld y = T[i] - x * W[i];
        for (int j = w; j >= 0; j--)
        {
            int k = min(w, j + W[i]);
            dp[k] = max(dp[k], dp[j] + y);
        }
    }

    //cout << x << "<- x, dp: " << dp[w] << "\n";
    return dp[w] >= 0;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> w;

    for (int i = 1; i <= n; i++)
        cin >> W[i] >> T[i];

    ld s = 0, e = 1e18;
    while (e - s > 0.000000001)
    {
        ld m = (s + e) / 2;
        if (able(m))
            s = m;
        else
            e = m;
        //cout << setprecision(20) << s << " " << e << "\n";
    }

    cout << (ll)(e * 1000);
}