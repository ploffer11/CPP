#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dp[3][120005][55];
vector<t> edge[3];
int p, n, m, dest[3];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    memset(dp, 0x11, sizeof(dp));

    cin >> p;
    for (int i = 0; i < p; i++)
    {
        cin >> n >> m;
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            edge[i].push_back({j, j, x});
        }
        while (m--)
        {
            int u, v, c;
            cin >> u >> v >> c;
            edge[i].push_back({v, u, c});
        }
        cin >> dest[i];

        dp[i][1][1] = 0;
        for (int j = 2; j <= 120000; j++)
        {
            for (auto [u, v, c] : edge[i])
            {
                dp[i][j][u] = min(dp[i][j][u], dp[i][j - 1][v] + c);
            }
        }
    }

    ll ans = (ll)1 << 62;
    for (int d = 1; d <= 120000; d++)
    {
        ll temp = 0;
        for (int i = 0; i < p; i++)
            temp += dp[i][d][dest[i]];
        ans = min(ans, temp);
    }
    cout << ans;
}