#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, ll> tt;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

ll dp[100005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int T = 1; T <= t; T++)
    {
        memset(dp, -1, sizeof(dp));

        int n, m;
        cin >> n >> m;

        dp[1] = 0;

        vector<tt> edge;
        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edge.push_back(tt(w, u, v));
        }

        sort(edge.begin(), edge.end());

        for (auto &e : edge)
        {
            auto w = get<0>(e);
            auto u = get<1>(e);
            auto v = get<2>(e);

            auto x = dp[u];
            auto y = dp[v];

            if (x != -1)
                dp[v] = max(dp[v], x + w);
            if (y != -1)
                dp[u] = max(dp[u], y + w);
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += dp[i];
        cout << "#" << T << " " << ans << "\n";
    }
}