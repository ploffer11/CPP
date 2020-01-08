#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

vector<pii> edge[50005];
vector<int> adj[100005];
int indegree[100005];
vector<int> sorted;
int n;

void topological(int m)
{
    sorted.clear();
    memset(indegree, 0, sizeof(indegree));
    for (int i = 1; i <= n; i++)
        adj[i].clear();

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= m; i++)
    {
        for (auto [u, v] : edge[i])
        {
            adj[u].push_back(v);
            indegree[v]++;
        }
    }

    for (int i = 1; i <= n; i++)
        if (!indegree[i])
            pq.push(i);

    while (!pq.empty())
    {
        auto node = pq.top();
        sorted.push_back(node);
        pq.pop();

        for (auto e : adj[node])
            if (--indegree[e] == 0)
                pq.push(e);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int x, u, v;
        cin >> x;

        if (x == 0)
            continue;
        else if (x == 1)
        {
            cin >> x;
            continue;
        }
        else
        {
            cin >> u;
            for (int j = 0; j < x - 1; j++)
            {
                cin >> v;
                edge[i].push_back({u, v});
                u = v;
            }
        }
    }

    int s = 1, e = m;

    while (s <= e)
    {
        int m = (s + e) / 2;
        topological(m);

        //cout << m << " " << sorted.size() << "\n";

        if (n == sorted.size())
            s = m + 1;
        else
            e = m - 1;
    }

    topological(e);
    for (auto i : sorted)
        cout << i << " ";
}