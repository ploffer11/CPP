#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const ll INF = 12345678987654321;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--)
    {
        vector<vector<pll>> adj;
        vector<ll> dis, check, cycle;

        int n, m, w;
        cin >> n >> m >> w;
        adj.resize(n + 1);
        dis.resize(n + 1, INF);
        check.resize(n + 1, 0);
        cycle.resize(n + 1, 0);

        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(pll(v, w));
            adj[v].push_back(pll(u, w));
        }

        while (w--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(pll(v, -w));
        }

        bool flag = false;

        for (int i = 1; i <= n; i++)
        {
            if (dis[i] == INF)
            {
                queue<int> q;
                q.push(i);
                check[i] = true;

                while (!q.empty())
                {
                    int s = q.front();
                    q.pop();
                    cycle[s]++;
                    check[s] = false;

                    if (cycle[s] == n)
                    {
                        flag = true;
                        break;
                    }

                    for (auto [e, w] : adj[s])
                    {
                        if (dis[e] > dis[s] + w)
                        {
                            dis[e] = dis[s] + w;
                            if (!check[e])
                            {
                                q.push(e);
                                check[e] = true;
                            }
                        }
                    }
                }
            }

            if (flag)
                break;
        }

        if (flag)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}