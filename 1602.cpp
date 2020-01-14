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
const int MAX = 505;

vector<int> dog[10005];
vector<pii> adj[MAX];

ll dis[MAX], V[MAX];
bool visit[MAX];

using tt = tuple<ll, ll, ll, int>;

ll dijk(int s, int e)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(visit, 0, sizeof(visit));
    priority_queue<tt> pq;

    dis[s] = 0;
    pq.push({V[s], V[s], 0, s});

    while (!pq.empty())
    {
        auto [x, m, cur, node] = pq.top();
        pq.pop();

        dis[node] = min(dis[node], x);

        if (visit[node])
            continue;

        for (auto [e, w] : adj[node])
        {   
            ll temp = max(m, V[e]);
            pq.push({cur + w + temp, temp, cur + w, e});
        }

        visit[node] = true;
    }

    return (dis[e] >= 1e18 ? -1 : dis[e]);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        V[i] = x;
    }

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    while (q--)
    {
        int x, y;
        cin >> x >> y;
        cout << dijk(x, y) << "\n";
    }
}