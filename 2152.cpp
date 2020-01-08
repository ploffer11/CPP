#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int N = 50005;

vector<int> adj[N], rev_adj[N], new_adj[N];
vector<int> st, temp;
vector<pii> edges;

int parent[N], dp[N], sz[N];
bool visit[N];

void dfs(int s, bool flag)
{
    if (visit[s])
        return;

    visit[s] = true;
    for (auto e : (flag ? adj[s] : rev_adj[s]))
        dfs(e, flag);

    (flag ? st : temp).push_back(s);
}

void topological_sort(int s)
{
    if (visit[s])
        return;

    visit[s] = true;
    for (auto e : new_adj[s])
        topological_sort(e);

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

    int n, m, s, e;
    cin >> n >> m >> s >> e;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        edges.push_back({u, v});
    }

    for (int i = 1; i <= n; i++)
        dfs(i, true);

    memset(visit, 0, sizeof(visit));

    while (!st.empty())
    {
        dfs(st.back(), false);
        st.pop_back();

        for (int i = 1; i < temp.size(); i++)
            uni(temp[0], temp[i]);

        temp.clear();
    }

    for (auto [u, v] : edges)
    {
        if (find(u) != find(v))
            new_adj[find(u)].push_back(find(v));
    }

    memset(visit, 0, sizeof(visit));
    topological_sort(find(s));
    dp[find(s)] = -parent[find(s)];

    while (st.back() != find(s))
        st.pop_back();

    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        //cout << s << " <- " << endl;

        for (auto e : new_adj[s])
            dp[e] = max(dp[e], dp[s] - parent[e]);
    }

    cout << dp[find(e)];
}