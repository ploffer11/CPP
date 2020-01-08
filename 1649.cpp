#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

int s, e, k;
int dp1[1005], dp2[1005], check[1005];
bool visit[1005];
vector<int> st;
vector<int> adj[1005], adj2[1005];

void dfs1(int s)
{
    visit[s] = true;
    for (auto e : adj[s])
        if (!visit[e])
            dfs1(e);
    st.push_back(s);
}

void dfs2(int s)
{
    int m = 0;
    for (auto e : adj[s])
        m = max(m, dp1[e]);
    dp1[s] = m + check[s];
}

void dfs3(int i)
{
    if (i == e)
        return;

    int m = 0;
    for (auto e : adj[i])
        m = max(m, dp1[e]);

    int x = 0;
    for (auto e : adj[i])
        if (dp1[e] == m)
            x += dp2[e];

    dp2[i] = x;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, t;
    cin >> n >> t;
    while (t--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj2[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!visit[i])
            dfs1(i);

    cin >> s >> e >> k;
    check[s] = check[e] = 1;
    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        check[x] = 1;
    }

    for (auto i : st)
        dfs2(i);

    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += check[i];

    if (dp1[s] != sum || dp1[e] != 1)
    {
        cout << "0";
        return 0;
    }
    
    dp2[e] = 1;

    for (auto i : st)
        dfs3(i);

    cout << dp2[s];
}