#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int dp[200005][22];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> dp[i][0];
    }

    for (int i = 1; i <= 20; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int a, b;
        cin >> a >> b;

        for (int i = 20; i >= 0; i--)
        {
            if (a >= (1 << i))
            {
                a -= (1 << i);
                b = dp[b][i];
            }
        }

        cout << b << '\n';
    }
}