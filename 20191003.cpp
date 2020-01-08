#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

class ExtendedGCD
{
private:
    vector<int> x, y, r, q;

    int gcd(int a, int b)
    {
        return (a % b == 0 ? b : gcd(b, a % b));
    }

public:
    // solve ax + by = c
    pii solve_equation(int a, int b, int c)
    {
        if (c % gcd(a, b) != 0)
            return {INF, INF};

        x = {1, 0};
        y = {0, 1};
        r = {a, b};

        while (1)
        {
            int r2 = r[r.size() - 2];
            int r1 = r[r.size() - 1];
            q.push_back(r2 / r1);
            r.push_back(r2 % r1);

            if (r[r.size() - 1] == 0)
                break;

            int x1 = x[x.size() - 1];
            int x2 = x[x.size() - 2];

            int y1 = y[y.size() - 1];
            int y2 = y[y.size() - 2];

            int q1 = q[q.size() - 1];
            x.push_back(x2 - x1 * q1);
            y.push_back(y2 - y1 * q1);
        }

        int mul = c / gcd(a, b);
        pii ret = {x[x.size() - 1] * mul, y[y.size() - 1] * mul};
        x.clear(), y.clear(), r.clear(), q.clear();
        return ret;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    ExtendedGCD egcd;
    ll n, p, a, b;
    cin >> n >> p >> a >> b;

    auto [x0, y0] = egcd.solve_equation(a, b, p);

    if (x0 == INF)
        return cout << "-1", 0;

    if (a * x0 + b * y0 == p && x0 >= 0 && y0 >= 0 && x0 + y0 <= n)
    {
        return cout << x0 << " " << y0 << " " << n - x0 - y0, 0;
    }

    ll d = gcd(a, b);
    //double MIN, MAX;
    double MAX = (double)(d * y0) / a;
    double MIN = max((double)(-d * x0) / b, (double)(n - x0 - y0) / (b - a));

    //cout << MIN << " " << MAX << "\n";

    for (ll k = MIN - 10; k <= MAX + 10; k++)
    {
        ll q = x0 + (b * k) / d, w = y0 - (a * k) / d;
        if (q >= 0 && w >= 0 && q + w <= n && a * q + b * w == p)
        {
            cout << q << " " << w << " " << n - q - w;
            return 0;
        }
    }
    cout << "-1";
}