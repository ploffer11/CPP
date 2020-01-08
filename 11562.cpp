#include <bits/stdc++.h>
using namespace std;

int dis[300][300];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    memset(dis, 0x3f, sizeof(dis));
    int n, m;

    cin >> n >> m;

    while (m--)
    {
        int u, v, b;
        cin >> u >> v >> b;
        if (b == 0)
        {
            dis[u][v] = 0;
            dis[v][u] = min(1, dis[v][u]);
        }

        else
        {
            dis[u][v] = 0;
            dis[v][u] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        cout << dis[a][b] << '\n';
    }
}