#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int parent[200005], win[200005], lose[200005];
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

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        uni(a, b);
        win[a]++;
        lose[b]++;
    }

    using t = tuple<int, int, int>;

    int max_size = -1;
    for (int i = 1; i <= n; i++)
    {
        max_size = max(max_size, -parent[find(i)]);
    }

    map<int, t> group;
    for (int i = 1; i <= n; i++)
    {
        int g = find(i);

        if (-parent[g] == max_size)
        {
            int w = win[i], l = lose[i];
            group[g] = max(group[g], {w, -l, -i});
        }
    }

    int ans = -INF;
    for (auto [_, value] : group)
    {
        auto [a, b, c] = value;
        ans = max(ans, c);
    }
    cout << -ans;
}