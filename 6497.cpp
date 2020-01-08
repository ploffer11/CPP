#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;

vector<t> edge;

int parent[200005];
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

    while (1)
    {
        memset(parent, -1, sizeof(parent));
        int n, m;
        cin >> n >> m;

        if (n + m == 0)
            return 0;

        int ans = 0;
        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;

            edge.push_back({w, u, v});
            ans += w;
        }

        sort(edge.begin(), edge.end());

        for (auto [w, u, v] : edge)
        {
            if (find(u) != find(v))
            {
                uni(u, v);
                ans -= w;
            }
        }
        edge.clear();

        cout << ans << '\n';
    }
}