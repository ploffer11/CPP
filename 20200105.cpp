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
const int MOD = 1e9 + 7;

int arr[101];
int dp[101][101][101][2];

int f(int i, int j, int k, int l)
{
    if (j < 0 || k < 0)
        return INF;

    if (i == 0)
        return 0;

    if (dp[i][j][k][l] != -1)
        return dp[i][j][k][l];

    if (arr[i] != 0 && arr[i] % 2 != l)
        return dp[i][j][k][l] = INF;

    if (arr[i] != 0 && arr[i] % 2 == 0)
    {
        int x = f(i - 1, j, k, 0);
        int y = f(i - 1, j, k, 1);

        return dp[i][j][k][l] = min(x, y + 1);
    }

    if (arr[i] != 0 && arr[i] % 2 == 1)
    {
        int x = f(i - 1, j, k, 0);
        int y = f(i - 1, j, k, 1);

        return dp[i][j][k][l] = min(x + 1, y);
    }

    if (l == 1)
    {
        int x = f(i - 1, j, k - 1, 0);
        int y = f(i - 1, j, k - 1, 1);

        return dp[i][j][k][l] = min(x + 1, y);
    }

    else
    {
        int x = f(i - 1, j - 1, k, 0);
        int y = f(i - 1, j - 1, k, 1);

        return dp[i][j][k][l] = min(x, y + 1);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    int even = n / 2;
    int odd = n / 2 + (n % 2 == 1);

    for (int i = 1; i <= n; i++)
    {
        if (arr[i] != 0 && arr[i] % 2 == 0)
            even -= 1;
        if (arr[i] != 0 && arr[i] % 2 == 1)
            odd -= 1;
    }

    cout << min(f(n, even, odd, 0), f(n, even, odd, 1));
}