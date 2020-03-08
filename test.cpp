#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tt = tuple<ll, int, int>;
//const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

bool visit[100'001][3];
ll dis[100'001][3];
vector<pii> adj[100'001];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        memset(dis, 0x3f, sizeof(dis));
        memset(visit, 0, sizeof(visit));

        int n, m, k;
        cin >> n >> m >> k;

        while (m--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            adj[x].push_back({y, z});
            adj[y].push_back({x, z});
        }

        int S, E;
        cin >> S >> E;
        priority_queue<tt, vector<tt>, greater<tt>> pq;
        pq.push({0, S, 0});
        dis[S][0] = 0;

        while (!pq.empty())
        {
            auto cur = get<0>(pq.top());
            auto s = get<1>(pq.top());
            auto warp = get<2>(pq.top());

            pq.pop();

            if (visit[s][warp])
                continue;

            visit[s][warp] = 1;
            for (auto &edge : adj[s])
            {
                auto e = edge.first, w = edge.second;
                if (dis[e][warp] > dis[s][warp] + w)
                {
                    dis[e][warp] = dis[s][warp] + w;
                    pq.push({dis[e][warp], e, warp});
                }

                if (warp <= k - 1 && dis[e][warp + 1] > dis[s][warp] + 1)
                {
                    dis[e][warp + 1] = dis[s][warp] + 1;
                    pq.push({dis[e][warp], e, warp + 1});
                }
            }
        }

        cout << min(min(dis[E][0], dis[E][1]), dis[E][2]) << "\n";

        for (int i = 1; i <= n; i++)
            adj[i].clear();
    }
}