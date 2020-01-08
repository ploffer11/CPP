#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

main()
{
    int n;
    cin >> n;

    vector<pair<ll, ll>> vt;
    for (int i = 0; i < n; i++)
    {
        ll x, y;
        scanf("%lld %lld", &x, &y);
        vt.push_back({x, 10 * y});
    }
    sort(vt.begin(), vt.end());

    ll s = 0, e = (ll)1 << 40;

    while (s <= e)
    {
        bool flag = false;
        ll m = (s + e) / 2;
        int i = 0;

        for (; i < n; i++)
        {
            if (vt[i].first == 0 && vt[i].second > m)
            {
                flag = true;
                break;
            }
            if (vt[i].second > m)
                break;
        }

        if (flag)
        {
            s = m + 1;
            continue;
        }

        if (i >= n - 1)
        {
            e = m - 1;
            continue;
        }

        ll low = vt[i].second, hi = vt[i].second;

        for (; i < n; i++)
        {
            if (hi - vt[i].second > 2 * m)
            {
                flag = true;
                break;
            }

            else if (vt[i].second - low > 2 * m)
                break;

            low = min(vt[i].second, low);
            hi = max(vt[i].second, hi);
        }

        if (flag)
        {
            s = m + 1;
            continue;
        }

        if (i >= n - 1)
        {
            e = m - 1;
            continue;
        }

        low = vt[i].second, hi = vt[i].second;

        for (; i < n; i++)
        {
            low = min(vt[i].second, low);
            hi = max(vt[i].second, hi);
            if (hi - low > 2 * m)
                break;
        }

        if (i == n)
            e = m - 1;
        else
            s = m + 1;
    }

    printf("%.1Lf", (long double)s / 10);
}