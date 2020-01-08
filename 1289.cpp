#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 100'005;

ll dp[MAX][2];
int visit[MAX];
vector<pii> adj[MAX];

void dfs(int s)
{
    for (auto [e, w] : adj[s])
    {
        if (!visit[e])
        {
            visit[e] = visit[s] + 1;
            dfs(e);
        }
    }
}

ll power(ll a, ll n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return a % MOD;

    ll b = power(a, n / 2);
    if (n % 2 == 0)
        return (b * b) % MOD;
    else
        return (b * b * a) % MOD;
}

ll f(int s, int flag)
{
    if (dp[s][flag] != -1)
        return dp[s][flag];

    ll ret = 0;
    if (flag)
    {
        for (auto [e, w] : adj[s])
        {
            if (visit[e] == visit[s] + 1)
            {
                ret += f(e, 1) * w + w;
                ret %= MOD;
            }
        }
    }

    else
    {
        for (auto [e, w] : adj[s])
        {
            if (visit[e] == visit[s] + 1)
            {
                ret += ((f(s, 1) - (f(e, 1) * w + w)) % MOD) * ((f(e, 1) * w + w) % MOD);
                ret %= MOD;
            }
        }

        ret = (ret * power(2, MOD - 2)) % MOD;

        for (auto [e, w] : adj[s])
        {
            if (visit[e] == visit[s] + 1)
            {
                ret += f(e, 0);
                ret %= MOD;
                ret += f(e, 1);
                ret %= MOD;
            }
        }
    }

    return dp[s][flag] = ret % MOD;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    visit[1] = 1;
    dfs(1);

    cout << (f(1, 0) + f(1, 1)) % MOD;
}