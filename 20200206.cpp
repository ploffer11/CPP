#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

ll dis[505][505];
bool added[505];
int add_order[505];
int ans[505];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        memset(dis, 0x3f, sizeof(dis));
        int n;
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                cin >> dis[i][j];
                dis[j][i] = dis[i][j];
            }
        }

        for (int i = n; i >= 1; i--)
            cin >> add_order[i];

        for (int k = 1; k <= n; k++)
        {
            int node = add_order[k];
            added[node] = true;

            for (int i = 1; i <= n; i++)
            {
                if (added[i])
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (added[j])
                        {
                            dis[i][j] = min(dis[i][j], dis[i][node] + dis[node][j]);
                        }
                    }
                }
            }
        }

        for (int k = 1; k <= n; k++)
        {
            int node = add_order[k];
            added[node] = true;
            for (int i = 1; i <= n; i++)
            {
                if (added[i])
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (added[j])
                        {
                            dis[i][j] = min(dis[i][j], dis[i][node] + dis[node][j]);
                        }
                    }
                }
            }
        }
    }