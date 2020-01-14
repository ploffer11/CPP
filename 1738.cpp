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
const int MAX = 101;

vector<pii> adj[MAX];
bool inq[MAX], can[MAX][MAX];
int via[MAX], cycle[MAX];
ll dis[MAX];

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
        can[u][v] = 1;
        adj[u].push_back({v, -w});
    }

    queue<int> q;
    q.push(1);
    inq[1] = true;
    dis[1] = 0;

    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        inq[s] = false;

        if (cycle[s] == n)
            continue;

        for (auto [e, w] : adj[s])
        {
            if (dis[e] > dis[s] + w)
            {
                dis[e] = dis[s] + w;
                via[e] = s;
                if (!inq[e])
                {
                    cycle[e]++;
                    q.push(e);
                    inq[e] = true;
                }
            }
        }
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                can[i][j] |= can[i][k] & can[k][j];

    for (int i = 1; i <= n; i++)
    {
        if (!can[1][n] || cycle[i] >= n && can[i][n])
        {
            cout << "-1";
            return 0;
        }
    }

    vector<int> ans;

    int cur = n;
    do
    {
        ans.push_back(cur);
        cur = via[cur];
    } while (cur != 1);

    cout << "1 ";
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << " ";
}