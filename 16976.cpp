#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 100'005;

int s[MAX], e[MAX];
vector<int> mid[MAX];
vector<int> game[MAX];
int parent[MAX];

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

    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        game[x].push_back(i);
    }

    for (int i = 1; i <= m; i++)
    {
        if (game[i].size() > 1)
            s[i] = 1, e[i] = q;
    }

    vector<pii> connect(q + 1);
    for (int i = 1; i <= q; i++)
    {
        int u, v;
        cin >> u >> v;
        connect[i] = {u, v};
    }

    while (1)
    {
        bool flag = true;
        for (int i = 1; i <= m; i++)
        {
            if (s[i] > 0 && s[i] <= e[i])
            {
                flag = false;
                mid[(s[i] + e[i]) / 2].push_back(i);
            }
        }
        if (flag)
            break;
        memset(parent, -1, sizeof(parent));

        for (int i = 1; i <= q; i++)
        {
            auto [u, v] = connect[i];
            uni(u, v);

            for (auto j : mid[i])
            {
                bool flag = true;
                for (int i = 1; i < game[j].size(); i++)
                    if (find(game[j][0]) != find(game[j][i]))
                        flag = false;

                if (flag)
                    e[j] = (s[j] + e[j]) / 2 - 1;
                else
                    s[j] = (s[j] + e[j]) / 2 + 1;
            }
            mid[i].clear();
        }
    }

    for (int i = 1; i <= m; i++)
    {
        cout << (s[i] > q ? -1 : s[i]) << '\n';
    }
}