#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define X first
#define Y second
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using ld = long double;
using pld = pair<ld, ll>;
using pll = pair<ll, ll>;

class ConvexHull
{
private:
    const ll INF = 98765432123456789;
    pll first = {INF, INF};
    vector<pll> points;

    pld converter(const pll &dot)
    {
        auto [x1, y1] = dot;
        auto [x2, y2] = first;
        auto dx = x2 - x1, dy = y2 - y1;
        if (x1 == x2)
            return {INF, dx * dx + dy * dy};
        else
            return {(ld)dy / dx, dx * dx + dy * dy};
    }

    ll outer_product(const pll &a, const pll &b, const pll &c)
    {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        auto [x3, y3] = c;
        return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    }

public:
    void add_point(int x, int y)
    {
        points.push_back({x, y});
        first = min(first, points.back());
    }

    vector<pll> convex_hull()
    {

        vector<pll> vt;
        sort(points.begin(), points.end(), [&](const pll &a, const pll &b) { return converter(a) < converter(b); });
        vt.push_back(first);

        for (auto &p : points)
        {
            if (p == first)
                continue;
            while (vt.size() >= 2)
            {
                int k = vt.size() - 1;
                auto &a = vt[k], &b = vt[k - 1];
                if (outer_product(b, a, p) >= 0)
                {
                    if (outer_product(b, a, p) == 0)
                        vt.pop_back();
                    break;
                }
                else
                    vt.pop_back();
            }
            vt.push_back(p);
        }

        return vt;
    }
};

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
    bool in_convex_hull(pll a, vector<pll> &vt)
    {
        for (int i = 1; i <= vt.size(); i++)
            if (ccw(vt[i % vt.size()], a, vt[(i - 1) % vt.size()]) < 0)
                return false;

        return true;
    }

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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    CCW ccw;
    ConvexHull CH;

    ll x, y;
    pll a, b, c;
    cin >> x >> y;
    a = {x, y};
    CH.add_point(x, y);
    cin >> x >> y;
    b = {x, y};
    CH.add_point(x, y);
    cin >> x >> y;
    c = {x, y};
    CH.add_point(x, y);

    vector<pll> ch = CH.convex_hull();
    int n, ans = 0;
    cin >> n;
    while (n--)
    {
        cin >> x >> y;
        if (ccw.in_convex_hull(pll(x, y), ch))
            ans++;
    }

    printf("%.1f\n%d", (double)abs(a.X * (b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X * (a.Y - b.Y)) / 2, ans);
}