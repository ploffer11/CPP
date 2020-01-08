#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tt = tuple<int, ll, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 1005;

ll dis[2 * MAX][MAX];
bool found[2 * MAX][MAX];
bool color[MAX];

vector<pii> adj[MAX];

pll dijk(int s, int e)
{
    memset(dis, 0x11, sizeof(dis));
    dis[0][0] = 0;
    priority_queue<tt, vector<tt>, greater<tt>> pq;
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        auto [change, cur, node] = pq.top();
        pq.pop();

        if (change == MAX || found[change][node])
            continue;

        for (auto [e, cost] : adj[node])
        {
            int C = change + (color[e] != color[node]);
            if (dis[C][e] > cur + cost)
            {
                dis[C][e] = cur + cost;
                pq.push({C, cur + cost, e});
            }
        }

        found[change][node] = true;
    }

    for (int i = 0; i < 2 * MAX; i++)
        if (dis[i][e] < 0x1111111111111111)
            return {i, dis[i][e]};
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> color[i];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            if (x)
                adj[i].push_back({j, x});
        }
    }

    auto [x, y] = dijk(0, m);
    cout << x << " " << y;
}