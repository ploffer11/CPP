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
const int MAX = 100000;

long double reach[23][MAX];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<int> adj[25];

    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    reach[0][0] = 1;

    long double ans = 0;
    for (int i = 0; i < MAX - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            for (auto k : adj[j])
            {
                //cout << j << " -> " << k << " : " << reach[j][i] << " " << adj[j].size() << " " << i << "\n";
                reach[k][i + 1] += (reach[j][i] / adj[j].size());
            }
        }

        ans += reach[n - 1][i + 1] * (i + 1);
        //cout << (reach[n - 1][i + 1]) << " " << (i + 1) << "\n";
    }

    cout << setprecision(20) << ans;
}