#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

using tt = tuple<int, int, int, int>;
vector<tt> vt;

int H[25], W[25], P[25];

int n, h;
ll dp[1 << 20 | 1], dp2[1 << 20 | 1];
ll ans = -INF;

ll f(int bit, ll w_sum, ll h_sum)
{
    dp2[bit] = h_sum;

    if (bit == 0)
        return dp[bit] = INF;

    if (dp[bit] != -1)
        return dp[bit];

    ll ret = -INF;
    for (int i = 0; i < n; i++)
    {
        if (bit & (1 << i))
        {
            ret = max(ret, min(f(bit ^ (1 << i), w_sum - W[i], h_sum - H[i]), P[i] - (w_sum - W[i])));
        }
    }

    return dp[bit] = ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    cin >> n >> h;

    ll w_sum = 0, h_sum = 0;
    for (int i = 0; i < n; i++)
    {
        int h, w, p;
        cin >> h >> w >> p;
        H[i] = h;
        W[i] = w;
        P[i] = p;
        dp[1 << i] = p;
        h_sum += h;
        w_sum += w;
    }

    f((1 << n) - 1, w_sum, h_sum);

    ll ans = -INF;
    for (int i = 0; i < (1 << n); i++)
        if (dp2[i] >= h)
            ans = max(ans, dp[i]);

    if (ans < 0)
        cout << "Mark is too tall";
    else
        cout << ans;
}