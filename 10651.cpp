#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    vector<pll> cow(n);

    for (int i = 0; i < n; i++)
        cin >> cow[i].first >> cow[i].second;

    sort(cow.begin(), cow.end());

    auto chk = [&](int m) {
        vector<vector<pll>> vt(m);

        for (int i = 0; i < n; i++)
        {
            bool flag = false;
            for (int j = 0; j < m; j++)
            {
                if (vt[j].empty())
                {
                    vt[j].push_back(cow[i]);
                    flag = true;
                }
                else
                {
                    auto [pos, v] = vt[j].back();
                    if (pos + v * t < cow[i].first + cow[i].second * t)
                    {
                        vt[j].push_back(cow[i]);
                        flag = true;
                    }
                }

                if (flag)
                    break;
            }
            if (!flag)
                return false;
        }
        return true;
    };

    int s = 0, e = n;
    while (s <= e)
    {
        int m = (s + e) >> 1;
        if (chk(m))
            e = m - 1;
        else
            s = m + 1;
    }
    cout << s;
}