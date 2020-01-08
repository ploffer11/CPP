#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int dis[305][305], dis2[305][305];
int parent[305];
int n;

vector<vector<int>> vt;
vector<pii> edge;

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
    int t;
    cin >> t;

    while (t--)
    {
        memset(parent, -1, sizeof(parent));
        cin >> n;
        vt.resize(n + 1);

        for (int i = 1; i <= n; i++)
        {
            string inp;
            cin >> inp;
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = inp[j - 1] - '0';
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dis[i][j] && dis[j][i])
                    uni(i, j);
            }
        }

        for (int i = 1; i <= n; i++)
            vt[find(i)].push_back(i);

        vector<pii> ans_vt;
        for (auto &i : vt)
        {
            if (i.size() > 1)
            {
                for (int j = 0; j < i.size() - 1; j++)
                {
                    ans_vt.push_back({i[j], i[j + 1]});
                }
                ans_vt.push_back({i.back(), i.front()});
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if ((find(i) != find(j)) && dis[i][j])
                {
                    dis2[find(i)][find(j)] = 1;
                }
            }
        }

        for (int u = 1; u <= n; u++)
        {
            for (int v = 1; v <= n; v++)
            {
                if (dis2[u][v])
                {
                    bool flag = true;
                    for (int i = 1; i <= n; i++)
                    {
                        if (i != u && i != v && dis2[u][i] && dis2[i][v])
                        {
                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                        edge.push_back({u, v});
                }
            }
        }

        cout << ans_vt.size() + edge.size() << "\n";
        for (auto [u, v] : ans_vt)
            cout << u << " " << v << "\n";
        for (auto [u, v] : edge)
            cout << u << " " << v << "\n";
        cout << "\n";

        edge.clear();
        for (int i = 1; i <= n; i++)
        {
            vt[i].clear();
            for (int j = 1; j <= n; j++)
                dis2[i][j] = 0;
        }
    }
}