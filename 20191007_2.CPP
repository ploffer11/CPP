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

int cnt[500'005];
int n, k;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--)
    {
        ll ans = 0;

        cin >> n >> k;
        vector<tuple<int, int, int>> edge;

        for (int i = 1; i <= n - 1; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edge.push_back({-w, u, v});
        }
        sort(edge.begin(), edge.end());

        for (auto [w, u, v] : edge)
        {
            if (cnt[u] < k && cnt[v] < k)
            {
                cnt[u]++;
                cnt[v]++;
                ans -= w;
            }
        }

        cout << ans << "\n";

        for (int i = 1; i <= n; i++)
            cnt[i] = 0;
    }
}