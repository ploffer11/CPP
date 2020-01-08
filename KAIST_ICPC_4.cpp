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

int dis[505][505];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        dis[u][v] = 1;
    }

    for (int i = 1; i <= n; i++)
        dis[i][i] = 1;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] |= dis[i][k] & dis[k][j];

    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            cnt += dis[i][j];

        if (cnt == n)
            ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for (auto i : ans)
        cout << i << " ";
}