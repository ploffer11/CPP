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

const int UP = 0;
const int DOWN = 1;
const int ALL = 2;

int arr[2][10005];
int dp[3][10005];
int n, w;

int f(int i, int j)
{
    if (j <= 0)
        return 0;

    if (j == 1)
    {
        if (i == UP || i == DOWN)
            return 1;
        else
            return (arr[UP][1] + arr[DOWN][1] <= w ? 1 : 2);
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    int ret = INF;
    if (i == UP)
        ret = min(f(DOWN, j - 1) + (arr[UP][j - 1] + arr[UP][j] <= w ? 1 : 2), f(ALL, j - 1) + 1);
    if (i == DOWN)
        ret = min(f(UP, j - 1) + (arr[DOWN][j - 1] + arr[DOWN][j] <= w ? 1 : 2), f(ALL, j - 1) + 1);
    if (i == ALL)
        ret = min({
            f(ALL, j - 1) + (arr[UP][j] + arr[DOWN][j] <= w ? 1 : 2),
            f(DOWN, j - 1) + (arr[UP][j - 1] + arr[UP][j] <= w ? 1 : 2) + 1,
            f(DOWN, j - 1) + (arr[UP][j] + arr[DOWN][j] <= w ? 1 : 2) + 1,
            f(UP, j - 1) + (arr[DOWN][j - 1] + arr[DOWN][j] <= w ? 1 : 2) + 1,
            f(UP, j - 1) + (arr[UP][j] + arr[DOWN][j] <= w ? 1 : 2) + 1,
            f(ALL, j - 2) + (arr[UP][j - 1] + arr[UP][j] <= w ? 1 : 2) + (arr[DOWN][j - 1] + arr[DOWN][j] <= w ? 1 : 2),
            f(ALL, j - 2) + (arr[UP][j] + arr[DOWN][j] <= w ? 1 : 2) + (arr[UP][j - 1] + arr[DOWN][j - 1] <= w ? 1 : 2),
        });
    return dp[i][j] = ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> w;

        for (int i = 0; i < 2; i++)
            for (int j = 1; j <= n; j++)
                cin >> arr[i][j];

        if (n == 1)
        {
            cout << (arr[0][1] + arr[1][1] <= w ? 1 : 2) << "\n";
            continue;
        }

        int &a = arr[0][1];
        int &b = arr[1][1];
        int &c = arr[0][n];
        int &d = arr[1][n];

        memset(dp, -1, sizeof(dp));
        int ans = f(ALL, n);

        if (a + c <= w)
        {
            int _a = a, _c = c;
            a = w;
            c = w;

            memset(dp, -1, sizeof(dp));
            ans = min(ans, f(ALL, n) - 1);
            a = _a;
            c = _c;
        }

        if (b + d <= w)
        {
            int _b = b, _d = d;
            b = w;
            d = w;

            memset(dp, -1, sizeof(dp));
            ans = min(ans, f(ALL, n) - 1);
            b = _b;
            d = _d;
        }

        if (a + c <= w && b + d <= w)
        {
            a = w;
            b = w;
            c = w;
            d = w;

            memset(dp, -1, sizeof(dp));
            ans = min(ans, f(ALL, n) - 2);
        }

        cout << ans << "\n";
    }
}