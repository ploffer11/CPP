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

int price[105];
int dp[2][10005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> price[i];

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
            dp[i % 2][j] = 0;

        for (int j = 0; j <= k; j++)
        {
            for (int m = 0; j - m * price[i] >= 0; m++)
            {
                dp[i % 2][j] += dp[(i - 1) % 2][j - m * price[i]];
            }
            //cout << i << " " << j << " -> " << dp[i][j] << "\n";
        }
    }

    cout << dp[n % 2][k];
}
