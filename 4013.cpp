#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int n, m;
bool visit[500'005], rest[500'005];
int cash[500'005], total_cash[500'005];
int parent[500'005];
ll dp[500'005];
vector<int> adj[500'005], rev_adj[500'005], new_adj[500'005];
vector<int> st, temp;
vector<pii> edges;

void dfs(int s, bool flag)
{
    visit[s] = true;
    for (auto e : (flag ? adj[s] : rev_adj[s]))
    {
        if (!visit[e])
            dfs(e, flag);
    }
    (flag ? st : temp).push_back(s);
}

void topologica_sort(int s)
{
    visit[s] = true;
    for (auto e : new_adj[s])
    {
        if (!visit[e])
            topologica_sort(e);
    }
    st.push_back(s);
}

int find(int me)
{
    if (parent[me] < 0)
        return me;
    else
        return parent[me] = find(parent[me]);
}

void uni(int a, int b)
{
    a = find(a), b = find(b);
    if (a != b)
    {
        parent[a] += parent[b];
        parent[b] = a;
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        edges.push_back({u, v});
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> cash[i];
        sort(adj[i].begin(), adj[i].end());
        sort(rev_adj[i].begin(), rev_adj[i].end());
    }

    int s, p;
    cin >> s >> p;

    for (int i = 1; i <= p; i++)
    {
        int x;
        cin >> x;
        rest[x] = true;
    }

    for (int i = 1; i <= n; i++)
        if (!visit[i])
            dfs(i, true);

    memset(visit, 0, sizeof(visit));

    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        if (!visit[s])
            dfs(s, false);

        for (int i = 1; i < temp.size(); i++)
            uni(temp[0], temp[i]);

        temp.clear();
    }

    for (auto [u, v] : edges)
        if (find(u) != find(v))
            new_adj[find(u)].push_back(find(v));

    for (int i = 1; i <= n; i++)
    {
        total_cash[find(i)] += cash[i];
        if (rest[i])
            rest[find(i)] = rest[i];
    }

    memset(visit, 0, sizeof(visit));
    topologica_sort(find(s));

    dp[find(s)] = total_cash[find(s)];

    while (st.back() != find(s))
        st.pop_back();

    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        for (auto e : new_adj[s])
            dp[e] = max(dp[s] + total_cash[e], dp[e]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (rest[find(i)])
            ans = max(ans, dp[find(i)]);

    cout << ans;
}