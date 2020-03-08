#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

int n, l, t_sum = 0, ans = INF;
int dp[1 << 20];
int T[21];
vector<int> vt[21];

int f(int bit)
{
    if (bit == 0)
        return 0;
    if (dp[bit] != -1)
        return dp[bit];
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        if ((1 << i) & bit)
        {
            int x = f((1 << i) ^ bit);
            auto it = upper_bound(vt[i].begin(), vt[i].end(), x);
            if (it != vt[i].begin())
                x = max(x, *(--it) + T[i]);
            ret = max(ret, x);
        }
    }

    return dp[bit] = ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    cin >> n >> l;

    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> T[i] >> m;
        t_sum += T[i];
        while (m--)
        {
            int x;
            cin >> x;
            vt[i].push_back(x);
        }
        dp[1 << i] = T[i];
    }

    f((1 << n) - 1);

    int ans = INF;
    for (int i = 0; i < (1 << n); i++)
    {
        if (f(i) >= l)
        {
            ans = min(ans, __builtin_popcount(i));
        }
    }
    cout << (ans == INF ? -1 : ans);
}