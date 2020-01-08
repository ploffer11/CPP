#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int p, n, m;
int dest[3];
bool finish[55][120000];
ll dis[3][55][120000];
ll hotel[55];
vector<pll> adj[55];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x11, sizeof(dis));
    using t = tuple<ll, ll, ll>;

    cin >> p;

    for (int i = 0; i < p; i++)
    {
        memset(finish, 0, sizeof(finish));
        int n, m;
        cin >> n >> m;

        for (int j = 1; j <= n; j++)
            cin >> hotel[j];

        while (m--)
        {
            ll u, v, c;
            cin >> u >> v >> c;
            adj[u].push_back({v, c});
        }
        cin >> dest[i];

        dis[i][1][1] = 0;
        priority_queue<t, vector<t>, greater<t>> pq;
        pq.push({1, 0, 1});

        while (!pq.empty())
        {
            auto [day, cur, s] = pq.top();
            pq.pop();

            if (day == 50000 || finish[s][day])
                continue;

            if (dis[i][s][day + 1] > cur + hotel[s])
            {
                dis[i][s][day + 1] = cur + hotel[s];
                pq.push({day + 1, cur + hotel[s], s});
            }

            for (auto [e, cost] : adj[s])
            {
                if (dis[i][e][day + 1] > cur + cost)
                {
                    dis[i][e][day + 1] = cur + cost;
                    pq.push({day + 1, cur + cost, e});
                }
            }
            finish[s][day] = true;
        }

        for (int j = 1; j <= n; j++)
            adj[j].clear();
    }

    ll ans = (ll)1 << 62;
    for (int d = 1; d <= 50000; d++)
    {
        ll temp = 0;
        for (int i = 0; i < p; i++)
            temp += dis[i][dest[i]][d];
        ans = min(ans, temp);
    }
    cout << ans;
}
