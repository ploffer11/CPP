#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;
const int INF = 1000005;

int parent[100005];
pii ans[100005], query[100005], range[100005];
vector<t> edges;

int n, M, q;

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

    cin >> n >> M;
    for (int i = 0; i < M; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        edges.push_back({t, u, v});
    }
    sort(edges.begin(), edges.end());

    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        int u, v;
        cin >> u >> v;
        query[i] = {u, v};
        range[i] = {0, M - 1};
        ans[i] = {-1, -1};
    }

    while (1)
    {
        int flag = true;
        vector<int> mid[100005];
        for (int i = 1; i <= q; i++)
        {
            auto [s, e] = range[i];

            if (s <= e)
            {
                flag = false;
                mid[(s + e) / 2].push_back(i);
            }

            else if (s > e && s < M && ans[i] == pii(-1, -1))
            {
                flag = false;
                mid[s].push_back(i);
            }
        }

        if (flag)
            break;

        memset(parent, -1, sizeof(parent));
        for (int i = 0; i < M; i++)
        {
            auto [t, u, v] = edges[i];
            uni(u, v);

            for (auto j : mid[i])
            {
                auto [x, y] = query[j];
                auto [s, e] = range[j];

                if (s <= e)
                {
                    int m = (s + e) / 2;
                    if (find(x) == find(y))
                        range[j] = {s, m - 1};
                    else
                        range[j] = {m + 1, e};
                }

                else
                    ans[j] = {get<0>(edges[s]), -parent[find(x)]};
            }
        }
    }

    for (int i = 1; i <= q; i++)
    {
        auto [a, b] = ans[i];
        if (a == -1)
            cout << "-1\n";
        else
            cout << a << " " << b << '\n';
    }
}