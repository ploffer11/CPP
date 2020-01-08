#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = 12345678987654321;
pll points[500005];

int main()
{
    setbuf(stdout, NULL);
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        ll ans = 0;
        ll m, n;
        cin >> m >> n;

        for (int i = 0; i < n; i++)
        {
            ll a, b;
            cin >> a >> b;
            points[i] = pll(a, b);
        }

        sort(points, points + n);

        for (int i = 0; i < n; i++)
        {
            auto x1 = points[i].first, y1 = points[i].second;
            ll cnt = INF;
            bool flag = true;

            // cout << "x1 y1: " << x1 << " " << y1 << endl;
            for (int j = i + 1; j < n; j++)
            {
                auto x2 = points[j].first, y2 = points[j].second;

                if (x2 >= x1 && y2 >= y1)
                {
                    cnt = min(max(x2 - x1, y2 - y1), cnt);
                    flag = false;
                }
            }

            if (flag)
                cnt = min(m - x1, m - y1);

            ans += cnt;
        }

        cout << "Case #" << t << endl;
        cout << ans << endl;
    }
}