#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 200005;

int ans = INF;
int n, k;

vector<pii> adj[MAX];
map<int, int> mp;

int sz[MAX];
bool del[MAX];

void dfs1(int s, int parent)
{
    sz[s] = 1;
    for (auto [e, _] : adj[s])
    {
        if (del[e] || parent == e)
            continue;
        dfs1(e, s);
        sz[s] += sz[e];
    }
}

int dfs2(int s, int parent, int cap)
{
    for (auto [e, _] : adj[s])
    {
        if (del[e] || parent == e)
            continue;
        if (sz[e] > cap)
            return dfs2(e, s, cap);
    }
    return s;
}

void dfs3(int s, int parent, int depth, int dist)
{
    if (dist > k)
        return;
    auto it = mp.find(k - dist);

    if (it != mp.end())
        ans = min(ans, it->second + depth);

    for (auto [e, w] : adj[s])
    {
        if (del[e] || parent == e)
            continue;
        dfs3(e, s, depth + 1, dist + w);
    }
}

void dfs4(int s, int parent, int depth, int dist)
{
    if (dist > k)
        return;

    auto it = mp.find(dist);

    if (it != mp.end())
        it->second = min(it->second, depth);
    else
        mp[dist] = depth;

    for (auto [e, w] : adj[s])
    {
        if (del[e] || parent == e)
            continue;
        dfs4(e, s, depth + 1, dist + w);
    }
}

void dfs5(int s)
{
    dfs1(s, -1);
    int cent = dfs2(s, -1, sz[s] / 2);
    del[cent] = true;

    mp.clear();
    mp[0] = 0;

    for (auto [e, w] : adj[cent])
    {
        if (!del[e])
        {
            dfs3(e, cent, 1, w);
            dfs4(e, cent, 1, w);
        }
    }

    for (auto [e, _] : adj[cent])
        if (!del[e])
            dfs5(e);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, x;
        cin >> u >> v >> x;
        u++, v++;
        adj[u].push_back({v, x});
        adj[v].push_back({u, x});
    }

    dfs5(1);
    cout << (ans == INF ? -1 : ans);
}