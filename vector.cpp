#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using pll = pair<ll, ll>;
class CCW
{
private:
    int ccw(pll a, pll b, pll c)
    {
        int op = a.first * b.second + b.first * c.second + c.first * a.second;
        op -= (a.second * b.first + b.second * c.first + c.second * a.first);
        if (op > 0)
            return 1;
        else if (op == 0)
            return 0;
        else
            return -1;
    }

public:
    bool is_intersect(pair<pll, pll> x, pair<pll, pll> y)
    {
        auto [a, b] = x;
        auto [c, d] = y;
        int ab = ccw(a, b, c) * ccw(a, b, d);
        int cd = ccw(c, d, a) * ccw(c, d, b);
        if (ab == 0 && cd == 0)
        {
            if (a > b)
                swap(a, b);
            if (c > d)
                swap(c, d);
            return c <= b && a <= d;
        }
        return ab <= 0 && cd <= 0;
    }
};
