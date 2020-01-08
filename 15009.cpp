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

int adj[30][30];
int n, m;

int dfs(int s, int money)
{
    for (int e = 1; e <= n; e++)
    {
        if (adj[s][e] == money)
        {
            adj[s][e] = 0;
            return dfs(e, money);
        }
    }
    return s;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;

    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        u++;
        v++;

        adj[u][v] += c;
    }

    for (int i = 1; i <= 100 * n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (j == k || adj[j][k] == 0)
                    continue;

                int x = dfs(k, adj[j][k]);

                if (j == x)
                {
                    adj[j][k] = 0;
                    continue;
                }

                adj[j][x] = adj[j][k];
                adj[j][k] = 0;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans += (adj[i][j] != 0);

    cout << ans;
}