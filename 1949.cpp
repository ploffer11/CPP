#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 10'005;

ll dp[MAX][2];
ll people[MAX];

int visit[MAX], visit2[MAX];
int cnt;

vector<int> adj[MAX];

void dfs(int s)
{
    for (auto e : adj[s])
        if (!visit[e])
        {
            visit[e] = visit[s] + 1;
            dfs(e);
        }
}

ll f(int s, int flag)
{
    if (dp[s][flag] != -1)
        return dp[s][flag];

    if (flag == 1)
    {
        ll ret = 0;
        for (auto e : adj[s])
        {
            if (visit[e] == visit[s] + 1)
                ret += f(e, 0);
        }
        return dp[s][1] = ret + people[s];
    }

    else
    {
        ll ret = 0;
        for (auto e : adj[s])
        {
            if (visit[e] == visit[s] + 1)
                ret += max(f(e, 0), f(e, 1));
        }
        return dp[s][0] = ret;
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> people[i];
    }

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    visit[1] = 1;
    dfs(1);

    cout << max(f(1, 0), f(1, 1)) << '\n';
}