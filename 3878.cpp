#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
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
    bool in_convex_hull(pll &a, vector<pll> &vt)
    {
        if (vt.size() == 1)
            return false;
        if (vt.size() == 2)
            return is_intersect({a, a}, {vt[0], vt[1]});

        if (ccw(vt[0], a, vt.back()) < 0)
            return false;

        for (int i = 1; i < vt.size(); i++)
            if (ccw(vt[i], a, vt[i - 1]) < 0)
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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        ConvexHull White, Black;

        int n, m;
        cin >> n >> m;

        for (int i = 1; i <= n; i++)
        {
            int x, y;
            cin >> x >> y;
            Black.add_point(x, y);
        }

        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            White.add_point(x, y);
        }

        auto vt1 = Black.convex_hull(), vt2 = White.convex_hull();
        vector<pair<pll, pll>> edge1, edge2;

        edge1.push_back({vt1[0], vt1.back()});
        for (int i = 1; i < vt1.size(); i++)
            edge1.push_back({vt1[i], vt1[i - 1]});

        edge2.push_back({vt2[0], vt2.back()});
        for (int i = 1; i < vt2.size(); i++)
            edge2.push_back({vt2[i], vt2[i - 1]});

        CCW ccw;
        bool flag = true;
        for (auto i : vt1)
            if (ccw.in_convex_hull(i, vt2))
                flag = false;

        for (auto i : vt2)
            if (ccw.in_convex_hull(i, vt1))
                flag = false;

        for (auto i : edge1)
            for (auto j : edge2)
                if (ccw.is_intersect(i, j))
                    flag = false;

        cout << (flag ? "YES\n" : "NO\n");
    }
}