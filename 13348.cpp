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

map<string, set<int>> mp;
map<string, bool> finish;
int cnt;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        string s, t;
        cin >> x >> y >> s >> t;

        if (i % 2 == m % 2)
        {
            if (s == t)
            {
                ans++;
                finish[s] = true;
                cnt++;
            }
            mp[s].insert(x);
            mp[t].insert(y);
        }
        else
        {
            if (s == t)
            {
                finish[s] = true;
                cnt++;
            }
        }
    }
    cout << "ans: " << ans << "\n";
    cout << ((ans != (n / 2)) ? ans + 1 : ans);
}