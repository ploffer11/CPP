#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9;

ll dp[205][205];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, K;
    cin >> N >> K;

    dp[0][0] = 1;
    for (int i = 1; i <= K; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            for (int k = j; k <= N; k++)
            {
                dp[i][k] += dp[i - 1][k - j];
                dp[i][k] %= MOD;
            }
        }
    }

    cout << dp[K][N];
}