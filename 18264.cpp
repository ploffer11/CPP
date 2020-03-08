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
const int MAX = 100001;

ll dis[26][26];
ll dp[MAX][26];
ll psum[MAX][26];
int arr[MAX];

int n, m, k;

ll f(int i, int j)
{
    if (i == 0)
        return 0;
    if (1 <= i && i <= k - 1)
        return INF;
    if (dp[i][j] != -1)
        return dp[i][j];

    ll ret = f(i - 1, j) + dis[arr[i]][j];

    ll dp_min = INF;
    ll cost = 0;
    for (int l = 0; l < m; l++)
    {
        dp_min = min(dp_min, f(i - k, l));

        int cnt = psum[i][l] - psum[i - k][l];
        cost += cnt * dis[l][j];
    }

    ret = min(ret, cost + dp_min);

    return dp[i][j] = ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    cin >> n >> m >> k;

    string s;
    cin >> s;

    for (int i = 1; i <= n; i++)
    {
        arr[i] = s[i - 1] - 'a';
        for (int j = 0; j < 26; j++)
        {
            psum[i][j] = psum[i - 1][j] + (j == arr[i]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> dis[i][j];
        }
    }

    for (int k = 0; k < m; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    ll ans = INF;
    for (int i = 0; i < m; i++)
        ans = min(ans, f(n, i));
    cout << ans;
}