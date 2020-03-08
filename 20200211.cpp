#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

int X[300005], Y[300005];
ll dp[300005][3][2];

void solve(int n, int x)
{
    memset(dp, 0, sizeof(dp));

    for (int j = 1; j <= 2; j++)
        dp[0][j][0] = dp[0][j][1] = -INF;

    for (int i = 0; i <= n; i++)
        dp[i][0][1] = -INF;

    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (j == 0)
            {
                dp[i][0][0] = dp[i - 1][0][0] + X[i];
            }
            else
            {
                dp[i][j][0] = max(dp[i - 1][j][1], dp[i - 1][j][0]) + X[i];
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0]) + Y[i];
            }
        }
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> X[i] >> Y[i];

        ll x_temp = X[n];
        ll y_temp = X[1];
        ll z_temp = Y[1] + Y[n];

        solve(n, n - 1);
        ll x = max(dp[n - 1][2][0], dp[n - 1][2][1]) + x_temp;

        for (int i = 1; i <= n - 1; i++)
        {
            X[i] = X[i + 1];
            Y[i] = Y[i + 1];
        }

        solve(n, n - 1);
        ll y = max(dp[n - 1][2][0], dp[n - 1][2][1]) + y_temp;

        for (int i = 1; i <= n - 2; i++)
            swap(X[i], Y[i]);

        solve(n, n - 2);
        ll z = max(dp[n - 2][2][0], dp[n - 2][2][1]) + z_temp;

        cout << "#" << t << " " << max({x, y, z}) << "\n";
    }
}