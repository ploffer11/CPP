#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

bool visit[100005];
int parent[100005];
ll color[3][100005];
ll cost[3][100005];
ll dp[3][100005];
vector<int> adj[100005];
int ans[100005];

void dfs(int i)
{
    for (auto e : adj[i])
    {
        if (!visit[e])
        {
            parent[e] = i;
            visit[e] = true;
            dfs(e);
        }
    }
}

ll fill_dp(int c, int i)
{
    //cout << c << " " << i << "\n";
    if (dp[c][i] != -1)
        return dp[c][i];

    ll ret = cost[c][i];
    for (auto e : adj[i])
    {
        if (parent[e] != i)
            continue;

        ll k = INF;
        for (int j = 0; j < 3; j++)
        {
            if (j == c)
                continue;
            k = min(k, fill_dp(j, e));
        }
        ret += k;
    }
    return dp[c][i] = ret;
}

void fill_ans(int c, int i)
{
    ans[i] = c;

    for (auto e : adj[i])
    {
        if (parent[e] != i)
            continue;

        ll k = INF, idx = -1;
        for (int j = 0; j < 3; j++)
        {
            if (j == c)
                continue;
            if (fill_dp(j, e) < k)
            {
                k = fill_dp(j, e);
                idx = j;
            }
        }
        fill_ans(idx, e);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;

    for (int j = 0; j < 3; j++)
        for (int i = 1; i <= n; i++)
            cin >> cost[j][i];

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    visit[1] = true;
    dfs(1);

    ll M = INF, idx = -1;
    for (int i = 0; i < 3; i++)
    {
        if (fill_dp(i, 1) < M)
        {
            M = fill_dp(i, 1);
            idx = i;
        }
    }
    fill_ans(idx, 1);

    cout << M << "\n";
    for (int i = 1; i <= n; i++)
        cout << ans[i] + 1 << " ";
}