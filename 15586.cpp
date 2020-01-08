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

int parent[100005], ans[100005];
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
    memset(parent, -1, sizeof(parent));
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edge, query;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        edge.push_back({c, u, v});
    }

    for (int i = 0; i < m; i++)
    {
        int k, v;
        cin >> k >> v;
        query.push_back({k, v, i});
    }

    sort(edge.begin(), edge.end());
    sort(query.begin(), query.end());

    reverse(edge.begin(), edge.end());
    reverse(query.begin(), query.end());

    int j = 0;
    for (auto [k, v, i] : query)
    {
        while (j < n - 1 && get<0>(edge[j]) >= k)
        {
            auto [_, x, y] = edge[j];
            //cout << k << " " << x << " " << y << "\n";
            uni(x, y);
            j++;
        }
        ans[i] = -parent[find(v)];
    }

    for (int i = 0; i < m; i++)
        cout << ans[i] - 1 << " ";
}