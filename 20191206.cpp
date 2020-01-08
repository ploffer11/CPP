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

bool check[300005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> ans;

        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            if (!check[u] && !check[v])
            {
                check[u] = check[v] = true;
                if (ans.size() < n)
                    ans.push_back(i);
            }
        }

        if (ans.size() == n)
        {
            cout << "Matching\n";
            for (int i = 0; i < n; i++)
                cout << ans[i] << " ";
            cout << "\n";

            for (int i = 1; i <= 3 * n; i++)
                check[i] = false;
        }
        else
        {
            ans.clear();
            for (int i = 1; i <= 3 * n; i++)
            {
                if (!check[i])
                {
                    if (ans.size() < n)
                        ans.push_back(i);
                }
                check[i] = false;
            }
            cout << "IndSet\n";
            for (auto i : ans)
                cout << i << " ";
            cout << "\n";
        }
    }
}