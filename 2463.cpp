#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9;

int parent[100005];
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
    int n, m;
    cin >> n >> m;
    vector<tuple<ll, int, int>> edge;

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge.push_back({-w, u, v});
    }

    sort(edge.begin(), edge.end());

    ll ans = 0;
    for (auto [w, u, v] : edge)
    {
        w = -w;
        uni(u, v);
        int sz = -parent[find(u)];
        // cout << sz * (sz - 1) / 2 << " " << w << "\n";
        ans += ((((sz * (sz - 1)) / 2) % MOD) * w) % MOD;
        ans %= MOD;
    }
    cout << ans;
}