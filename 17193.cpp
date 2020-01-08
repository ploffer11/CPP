#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const ll MOD = 2019201997;

int parent[7505];
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
ll f(ll x, ll y)
{
    return ((2019201913 * x) % MOD + ((2019201949) * y) % MOD) % MOD;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n, k;
    cin >> n >> k;

    int group = n;

    vector<tuple<ll, ll, ll>> query;

    for (ll i = 1; i <= n; i++)
    {
        for (ll j = i + 1; j <= n; j++)
        {
            query.push_back({f(i, j), i, j});
        }
    }

    sort(query.begin(), query.end());

    for (auto [x, y, z] : query)
    {
        if (find(y) != find(z))
        {
            if (group != k)
            {
                uni(y, z);
                group--;
            }
            else
            {
                cout << x;
                return 0;
            }
        }
    }
}