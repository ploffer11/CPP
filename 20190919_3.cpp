#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;

const int m = 100;
int a[300'005], b[300'005];
ll dp[300'005][m + 1];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x11, sizeof(dp));

    int q;
    cin >> q;
    while (q--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i] >> b[i];
        }

        bool flag = true;
        for (int i = 2; i <= n; i++)
        {
            if (a[i] == a[i - 1])
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            cout << "0\n";
            continue;
        }

        for (int j = 0; j <= m; j++)
            dp[1][j] = b[1] * j;

        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= m - 1; j++)
            {
            }
        }

        ll ans = 12345678987654321;

        for (int j = 0; j <= m; j++)
            ans = min(ans, dp[n][j]);

        cout << ans << "\n";

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
                dp[i][j] = INF;
    }
}