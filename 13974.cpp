#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

ll file[5005];
ll prefix[5005];
ll dp[5005][5005];
ll min_k[5005][5005];

ll sum(int l, int r)
{
    return prefix[r] - prefix[l - 1];
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x3f, sizeof(dp));

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> file[i];
            prefix[i] = prefix[i - 1] + file[i];
            dp[i][i] = 0;
            min_k[i][i] = i;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j + i <= n; j++)
            {
                for (int k = min_k[j][j + i - 1]; k <= min_k[j + 1][j + i]; k++)
                {
                    int m = dp[j][k] + dp[k + 1][j + i] + sum(j, k) + sum(k + 1, j + i);
                    if (dp[j][j + i] > m)
                    {
                        dp[j][j + i] = m;
                        min_k[j][j + i] = k;
                    }
                }
            }
        }

        cout << dp[1][n] << "\n";
        for (int i = 1; i <= n; i++)
        {
            file[i] = prefix[i] = 0;
            for (int j = 1; j <= n; j++)
                dp[i][j] = INF;
        }
    }
}