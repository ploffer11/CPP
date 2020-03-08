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

int n, m, k;
ll dis[2][200005];
int finish[2][200005];
vector<pii> adj[200005];

void dijk(int s, int x)
{
    using pp = pair<ll, int>;
    priority_queue<pp, vector<pp>, greater<pp>> pq;

    pq.push({0, s});
    dis[x][s] = 0;

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        if (finish[x][s])
            continue;

        for (auto [e, cost] : adj[s])
        {
            if (dis[x][e] > dis[x][s] + cost)
            {
                dis[x][e] = dis[x][s] + cost;
                pq.push({dis[x][e], e});
            }
        }

        finish[x][s] = true;
    }
}

bool color[200005];
main()
{
    memset(dis, 0x11, sizeof(dis));
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;

    vector<int> cow;
    for (int i = 1; i <= k; i++)
    {
        int x;
        cin >> x;
        cow.push_back(x);

        color[x] = true;
    }

    bool flag = false;
    vector<pii> save;
    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v;

        if (color[u] && color[v])
            flag = true;
        adj[u].push_back({v, 1});
        adj[v].push_back({u, 1});
    }

    dijk(1, 0);
    dijk(n, 1);

    if (flag)
    {
        cout << dis[0][n];
        return 0;
    }
    vector<int> vt1, vt2;
    for (auto i : cow)
    {
        vt1.push_back(dis[0][i]);
        vt2.push_back(dis[1][i]);
    }

    sort(vt1.begin(), vt1.end());
    sort(vt2.begin(), vt2.end());

    for (int i = 0; i < n; i++)
    {
        if (vt1[i] == vt1[i + 1])
        {
            cout << dis[0][n];
            return 0;
        }
    }
    int ans = -INF;
    for (auto i : vt1)
    {
        int idx = upper_bound(vt2.begin(), vt2.end(), dis[0][n] - i - 1) - vt2.begin();

        if (idx == 0)
            continue;
        else
            ans = max(ans, i + vt2[idx - 1] + 1);
    }

    if (ans == -INF)
        cout << dis[0][n];
    else
        cout << min((int)dis[0][n], ans);
}