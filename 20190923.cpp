#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int parent[7005];
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

int a[7005], b[7005];
bool flag[7005];
vector<int> group[7005];
vector<int> adj[7005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++)
        cin >> b[i];

    vector<pii> edge;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;

            if ((a[i] & a[j]) == a[i])
            {
                flag[i] = true;
                edge.push_back({i, j});
                adj[i].push_back(j);
            }
        }
    }

    for (int t = 0; t < n + 100; t++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (!flag[i])
                continue;
            bool f = false;
            for (auto e : adj[i])
            {
                if (flag[e])
                {
                    f = true;
                    break;
                }
            }
            flag[i] = f;
        }
    }

    for (auto [i, j] : edge)
        if (flag[i] && flag[j])
            uni(i, j);

    for (int i = 1; i <= n; i++)
        group[find(i)].push_back(b[i]);

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (group[i].size() >= 2)
        {
            ll m = 0;
            for (auto j : group[i])
                m += j;
            ans = max(ans, m);
        }
    }

    cout << ans;
}