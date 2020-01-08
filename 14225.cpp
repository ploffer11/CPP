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

bool dp[200'0005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    vector<int> vt;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vt.push_back(x);
    }
    dp[0] = true;
    for (auto i : vt)
        for (int j = 2000000; j - i >= 0; j--)
            dp[j] |= dp[j - i];

    for (int i = 0; i <= 2000000; i++)
        if (!dp[i])
            return cout << i, 0;
}