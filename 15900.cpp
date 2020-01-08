#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;

vector<int> adj[500005];
int depth[500005];
bool flag[500005];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<pii> q;
    q.push({1, 1});
    depth[1] = 1;

    while (!q.empty())
    {
        auto [d, s] = q.front();
        q.pop();
        for (auto e : adj[s])
        {
            if (!depth[e])
            {
                flag[s] = true;
                depth[e] = d + 1;
                q.push({d + 1, e});
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        //cout << depth[i] << " ";
        if (!flag[i])
            ans += depth[i] - 1;
    }
    //cout << endl;

    //cout << ans << '\n';
    cout << (ans % 2 == 1 ? "Yes" : "No");
}