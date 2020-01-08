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

vector<pii> adj[100005];
int visit[100005];
int degree[100005];

ll ans = 0;

using tt = tuple<int, ll, ll>;
tt dfs(int x)
{
    visit[x] = true;

    bool leaf = true;

    int cnt_sum = 0;
    ll s_sum = 0;
    ll p_sum = 0;

    vector<tt> temp;

    for (auto [e, w] : adj[x])
    {
        if (!visit[e])
        {
            leaf = false;

            auto [cnt, s, p] = dfs(e);

            p = p + cnt * w * w + 2 * w * s;
            s = cnt * w + s;

            cnt_sum += cnt;
            s_sum += s;
            p_sum += p;

            temp.push_back({cnt, s, p});
        }
    }

    if (leaf)
        return {1, 0, 0};

    for (auto [cnt, s, p] : temp)
    {
        ans += (cnt_sum - cnt) * p;
        ans += (s_sum - s) * s;
    }

    return {cnt_sum, s_sum, p_sum};
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
        degree[u]++;
        degree[v]++;
    }

    int s = -1;
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] >= 2)
        {
            s = i;
            break;
        }
    }

    dfs(s);

    cout << ans;
}