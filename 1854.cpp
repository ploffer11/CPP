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
priority_queue<int, vector<int>, less<int>> dis[1005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    while (m--)
    {
        int u, v, x;
        cin >> u >> v >> x;
        adj[u].push_back({v, x});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dis[1].push(0);
    pq.push({0, 1});

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        for (auto [e, w] : adj[s])
        {
            if (dis[e].size() < k)
            {
                dis[e].push(cur + w);
                pq.push({cur + w, e});
            }

            else if (dis[e].top() > cur + w)
            {
                dis[e].pop();
                dis[e].push(cur + w);
                pq.push({cur + w, e});
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (dis[i].size() == k)
            cout << dis[i].top() << "\n";
        else
            cout << "-1\n";
    }
}