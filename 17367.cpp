#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

double price(int i, int j, int k)
{
    if (i == j && j == k)
        return 10000 + i * 1000;
    else if (i == j || j == k || i == k)
    {
        int x = (i == j ? i : (j == k ? j : i));
        return 1000 + x * 100;
    }
    else
        return max(max(i, j), k) * 100;
}

double dp[1002][7][7][7];

double f(int n, int i, int j, int k)
{
    if (dp[n][i][j][k] != -1.0)
        return dp[n][i][j][k];

    double ret = 0;
    for (int m = 1; m <= 6; m++)
        ret += f(n + 1, j, k, m);

    return dp[n][i][j][k] = max(price(i, j, k) / 216, ret / 6);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int m = 1; m <= 1000; m++)
        for (int i = 1; i <= 6; i++)
            for (int j = 1; j <= 6; j++)
                for (int k = 1; k <= 6; k++)
                    dp[m][i][j][k] = -1.0;

    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
            for (int k = 1; k <= 6; k++)
                dp[n][i][j][k] = price(i, j, k) / 216;

    double ans = 0;
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
            for (int k = 1; k <= 6; k++)
                ans += f(3, i, j, k);

    printf("%.10f", ans);
}