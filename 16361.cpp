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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<pair<ll, ll>> vt;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        vt.push_back({x, y});
    }

    sort(vt.begin(), vt.end());

    using ld = long double;

    ld s = 0, e = (ll)1 << 40;

    while (e - s > (ld)1e-9)
    {
        bool flag = false;
        ld m = (s + e) / 2;
        int i = 0;

        for (; i < n; i++)
        {
            if (vt[i].second > m)
                break;
        }

        if (n - i <= 2)
        {
            e = m;
            continue;
        }

        ll low = vt[i].second, hi = vt[i].second;

        for (i++; i < n; i++)
        {
            if (hi - vt[i].second > 2 * m)
            {
                flag = true;
                break;
            }

            low = min(vt[i].second, low);
            hi = max(vt[i].second, hi);

            if (hi - low > 2 * m)
                break;
        }

        if (flag)
        {
            s = m;
            continue;
        }

        if (n - i <= 1)
        {
            e = m;
            continue;
        }

        low = vt[i].second, hi = vt[i].second;

        for (i++; i < n; i++)
        {
            low = min(vt[i].second, low);
            hi = max(vt[i].second, hi);
            if (hi - low > 2 * m)
                break;
        }

        if (i == n)
            e = m;
        else
            s = m;
    }

    printf("%.1Lf", s);
}