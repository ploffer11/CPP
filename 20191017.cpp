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

ll cost[50005], sz[50005];
int parent[50005], visit[5005];
vector<pii> adj[50005];

void dfs(int s)
{
    sz[s] = 1;
    for (auto [e, w] : adj[s])
    {
        if (!visit[e])
        {
            sz[s]++;
            visit[e] = true;
            dfs(e);
        }
    }
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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    vector<tuple<int, int, int>> edge;
    int n, m;
    cin >> n >> m;

    ll x = INF;
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i];
        x = min(x, cost[i]);
    }

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge.push_back({2 * c + cost[a] + cost[b], a, b});
    }

    sort(edge.begin(), edge.end());

    ll ans = 0;
    for (auto [w, u, v] : edge)
    {
        if (find(u) != find(v))
        {
            uni(u, v);
            ans += w;
        }
    }

    cout << ans + x;
}