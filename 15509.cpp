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

int parent[1005];
int dp[1005];
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

    int n, k, m;
    cin >> n >> m >> k;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        uni(u, v);
    }

    vector<int> vt;
    for (int i = 1; i <= n; i++)
        vt.push_back(find(i));

    sort(vt.begin(), vt.end());
    vt.resize(unique(vt.begin(), vt.end()) - vt.begin());
    for (auto &i : vt)
        i = -parent[i];

    n = vt.size();
    dp[0] = 1;

    for (auto i : vt)
        for (int j = 1000; j - i >= 0; j--)
            dp[j] |= dp[j - i];

    cout << (dp[k] ? "SAFE" : "DOOMED");
}