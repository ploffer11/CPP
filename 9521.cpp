#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll dp[1000005], n, k;

ll f(ll a, ll b)
{
    return ((a % MOD) + (b % MOD)) % MOD;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k;

    dp[1] = k;
    dp[2] = k * (k - 1) % MOD;
    
    for (int i = 3; i <= 1000001; i++)
        dp[i] = f(dp[i - 1] * (k - 2), dp[i - 2] * (k - 1));

    vector<int> to(n + 1), visit(n + 1, 0), start_node(n + 1), ans;
    for (int i = 1; i <= n; i++)
        cin >> to[i];

    int cnt = 1;
    for (int i = 1; i <= n; i++)
    {
        if (!visit[i])
        {
            int j = i;
            for (; !visit[j]; j = to[j])
            {
                visit[j] = cnt++;
                start_node[j] = i;
            }

            if (start_node[j] == i)
                ans.push_back(cnt - visit[j]);
        }
    }

    ll ans2 = 1, m = n;
    for (int i = 0; i < ans.size(); i++)
    {
        ans2 *= dp[ans[i]];
        ans2 %= MOD;
        m -= ans[i];
    }

    for (int i = 1; i <= m; i++)
    {
        ans2 *= k - 1;
        ans2 %= MOD;
    }

    cout << ans2;
}