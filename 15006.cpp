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
const int MAX = 100'005;

int n;
pll via[MAX];
ll dis[MAX];
bool finish[MAX];
vector<pll> adj[MAX];

void dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
        dis[i] = INF;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});
    dis[s] = 0;

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        if (finish[s])
            continue;

        for (auto [e, cost] : adj[s])
        {
            if (dis[e] > cur + cost)
            {
                via[e] = {s, cost};
                dis[e] = cur + cost;
                pq.push({dis[e], e});
            }
        }

        finish[s] = true;
    }

    memset(finish, 0, sizeof(finish));
}

map<tuple<int, int, int>, bool> edge;
vector<int> ans;

void f(int e)
{
    auto [s, cost] = via[e];
    edge[{e, s, cost}] = false;
    edge[{s, e, cost}] = false;
}

void g(int e)
{
    ans.push_back(e);
    if (via[e].first == 0)
        return;
    g(via[e].first);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(via, -1, sizeof(via));

    int m;
    cin >> n >> m;

    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        u++;
        v++;
        adj[v].push_back({u, c});
        adj[u].push_back({v, c});
        edge[{u, v, c}] = true;
        edge[{v, u, c}] = true;
    }

    dijkstra(2);

    for (int i = 1; i <= n; i++)
        f(i);

    for (int i = 1; i <= n; i++)
    {
        adj[i].clear();
        via[i] = {0, 0};
    }

    for (auto [t, flag] : edge)
    {
        if (flag)
        {
            auto [u, v, c] = t;
            adj[u].push_back({v, c});
        }
    }

    dijkstra(1);
    //cout << dis[2] << endl;

    if (dis[2] == INF)
    {
        cout << "impossible";
        return 0;
    }

    g(2);

    cout << ans.size() << " ";
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i] - 1 << " ";
    }
}