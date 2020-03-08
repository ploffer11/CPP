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

vector<pii> adj[1005];
bool finish[1005];
int via[1005];
ll dis[1005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dis[1] = 0;
    pq.push({0, 1});

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
                via[e] = s;
                dis[e] = cur + w;
                pq.push({dis[e], e});
            }
        }
        finish[s] = true;
    }

    cout << n - 1 << "\n";
    for (int i = 2; i <= n; i++)
    {
        cout << i << " " << via[i] << "\n";
    }
}