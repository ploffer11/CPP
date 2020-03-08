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

int cost[1005][3];
ll dp[1005][3];

ll f(int i, int j, int first_color)
{
    if (i == 1)
        return (j == first_color ? cost[i][j] : INF);

    if (dp[i][j] != -1)
        return dp[i][j];

    ll ret = INF;
    for (int k = 0; k < 3; k++)
        if (k != j)
            ret = min(ret, f(i - 1, k, first_color));
    return dp[i][j] = ret + cost[i][j];
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> cost[i][j];
        }
    }
    ll ans = INF;

    memset(dp, -1, sizeof(dp));
    ans = min({ans, f(n, 1, 0), f(n, 2, 0)});

    memset(dp, -1, sizeof(dp));
    ans = min({ans, f(n, 0, 1), f(n, 2, 1)});

    memset(dp, -1, sizeof(dp));
    ans = min({ans, f(n, 0, 2), f(n, 1, 2)});

    cout << ans;
}