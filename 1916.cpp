#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int dis[1005];
vector<pii> adj[1005];
bool check[1005];
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int s, e;
    cin >> s >> e;

    queue<int> q;
    q.push(s);
    check[s] = true;
    dis[s] = 0;

    while (!q.empty())
    {
        auto s = q.front();
        q.pop();
        check[s] = false;

        for (auto [e, weight] : adj[s])
        {
            if (dis[e] > dis[s] + weight)
            {
                dis[e] = dis[s] + weight;
                if (!check[e])
                {
                    q.push(e);
                    check[e] = true;
                }
            }
        }
    }

    cout << dis[e];
}