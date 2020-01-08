#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int parent[200005];
int query[200005];
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

    while (m--)
    {
        int x, y;
        cin >> x >> y;
        int l = min(x, y), r = max(x, y);
        uni(x, y);

        query[l] = max(query[l], r);
    }

    int ans = 0, prev = 0;
    for (int i = 1; i <= n; i++)
    {
        if (query[i] == 0)
            continue;

        for (int j = max(i, prev); j < query[i]; j++)
        {
            if (find(i) != find(j))
            {
                ans++;
                uni(i, j);
            }
        }

        prev = max(prev, query[i]);
    }

    cout << ans;
}