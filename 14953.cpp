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

bool visit[100005];
int indegree[100005];
ll dp[100005];
vector<pii> edges;
vector<int> adj[100005];

stack<int> st;

void dfs(int s)
{
    visit[s] = true;
    for (auto e : adj[s])
        if (!visit[e])
            dfs(e);
    st.push(s);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        u++;
        v++;
        edges.push_back({u, v});
        edges.push_back({v, u});
        indegree[u]++;
        indegree[v]++;
    }

    for (auto [u, v] : edges)
    {
        if (indegree[u] < indegree[v])
            adj[u].push_back(v);
        else if (indegree[u] > indegree[v])
            adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!visit[i])
            dfs(i);

    while (!st.empty())
    {
        int s = st.top();
        st.pop();

        for (auto e : adj[s])
            dp[e] = max(dp[e], dp[s] + 1);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i]);
    }

    cout << ans + 1;
}