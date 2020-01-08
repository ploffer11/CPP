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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        ConvexHull CH;
        int x;
        cin >> x;
        while (x--)
        {
            int a, b;
            cin >> a >> b;
            CH.add_point(a, b);
        }

        auto vt = CH.convex_hull();

        ll idx = -1, mx = INF, my = -1;
        for (int i = 0; i < vt.size(); i++)
        {
            auto [x, y] = vt[i];
            if (y > my)
            {
                idx = i;
                mx = x;
                my = y;
            }
            else if (y == my)
            {
                if (x <= mx)
                {
                    idx = i;
                    mx = x;
                }
            }
        }

        cout << vt.size() << "\n";

        for (int i = idx; i >= 0; i--)
            cout << vt[i].first << " " << vt[i].second << '\n';

        for (int i = vt.size() - 1; i > idx; i--)
            cout << vt[i].first << " " << vt[i].second << '\n';
    }
}