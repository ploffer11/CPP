#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 3;

ll dp[1005][1005];

ll f(int i, int j)
{
    if (i < 0)
        return 0;
    if (i != 0 && j == 0)
        return 1;
    if (i != 0 && j == 1)
        return i;

    if (dp[i][j] != -1)
        return dp[i][j];

    return dp[i][j] = (f(i - 2, j - 1) + f(i - 1, j)) % MOD;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n, k;
    cin >> n >> k;

    cout << (f(n - 3, k - 1) + f(n - 1, k)) % MOD;
}