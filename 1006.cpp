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

int arr[3][10005];
int dp[3][10005];
int n, w;

int f(int i, int j)
{

    if (dp[i][j] != -1)
        return dp[i][j];

    int g = 0, h = 0;
    if (j >= 2)
        g = arr[1][i - 2], h = arr[2][i - 2];

    int a = arr[1][i - 1], b = arr[2][i - 1];
    int c = arr[1][i], d = arr[2][i];

    int &x = dp[i][j];
    int _1 = f(1, i - 1), _2 = f(2, i - 1), _3 = f(1, i - 2), _4 = f(2, i - 2);

    if (c + d <= w)
        x = min(x, _1 + _2 + 1);
    else
        x = min(x, _1 + _2 + 2);

    if (a + c <= w && b + d <= w)
        x = min(x, _3 + _4 + 2);
    if (a + c <= w)
        x = min(x, _3 + _2 + 1);
    if (b + d <= w)
        x = min(x, _4 + _1 + 1);

    return dp[i][j] = x;
}

void init(bool flag)
{
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[j] = -1;
            if (flag)
                arr[i][j] = 0;
        }
    }
}
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> w;

        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= n; j++)
                cin >> arr[i][j];

        auto [a, b, c, d] = tuple<int, int, int, int>(arr[1][1], arr[2][1], arr[1][n], arr[2][n]);

        int x = f(n, 0);
        init(false);

        arr[1][1] = arr[2][1] = 0;

        int y = f(n - 1, 1);
        init(true);

        cout << x << " < - >  " << y << "\n";
        if (a + c <= w && b + d <= w)
            cout << min(x, y + 2) << "\n";
        else if (a + c <= w || b + d <= w)
            cout << min(x, y + 3) << "\n";
        else
            cout << min(x, y + 4) << "\n";
    }
}