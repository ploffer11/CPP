#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll arr[200005], dp[200005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++)
        cin >> arr[i];

    dp[2] = arr[2];
    for (int i = 3; i <= n; i++)
        dp[i] = dp[i - 1] ^ arr[i];

    while (q--)
    {
        ll c, x, y, d;
        cin >> c >> x >> y;

        ll z = dp[x] ^ dp[y];

        if (c == 0)
        {
            cout << z << "\n";
        }
        else
        {
            cin >> d;
            cout << (z ^ d) << "\n";
        }
    }
}