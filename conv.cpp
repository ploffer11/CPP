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
    const ll INF = (ll)1 << 60;
    pll first = {INF, INF};
    vector<pll> points;

    pld converter(const pll &a)
    {
        auto [x1, y1] = a;
        auto [x2, y2] = first;
        auto dx = x1 - x2, dy = y1 - y2;
        auto d = dx * dx + dy * dy;

        return (x1 == x2 ? pld(INF, d) : pld((ld)dy / dx, d));
    }

    ll outer_product(const pll &a, const pll &b, const pll &c)
    {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        auto [x3, y3] = c;

        return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    }

public:
    void add_point(ll x, ll y)
    {
        points.push_back({x, y});
        first = min(first, points.back());
    }

    vector<pll> convex_hull()
    {
        sort(points.begin(), points.end(), [&](const pll &a, const pll &b) { return converter(a) < converter(b); });
        vector<pll> vt;
        vt.push_back(first);

        for (auto &p : points)
        {
            while (vt.size() >= 2)
            {
                int op = outer_product(vt[vt.size() - 2], vt.back(), p);
                if (op >= 0)
                {
                    if (op == 0)
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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    ConvexHull CH;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        CH.add_point(a, b);
    }

    cout << CH.convex_hull().size();
}