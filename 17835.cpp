#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

bool finish[100005];
ll dis[100005];
vector<pii> adj[100005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));

    int n, m, k;
    cin >> n >> m >> k;
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[v].push_back({u, w});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    while (k--)
    {
        int x;
        cin >> x;
        dis[x] = 0;
        pq.push({0, x});
    }

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        if (finish[s])
            continue;

        for (auto [e, w] : adj[s])
        {
            if (dis[e] > cur + w)
            {
                dis[e] = cur + w;
                pq.push({dis[e], e});
            }
        }

        finish[s] = true;
    }

    ll ans = -1;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dis[i]);

    for (int i = 1; i <= n; i++)
    {
        //cout << dis[i] << " <- \n";
        if (dis[i] == ans)
        {
            cout << i << "\n"
                 << dis[i];
            return 0;
        }
    }
}