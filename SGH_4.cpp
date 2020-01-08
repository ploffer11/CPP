#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
using pld = pair<ld, ll>;
using pll = pair<ll, ll>;

const ll INF = 98765432123456789;

pll first = {INF, INF};
vector<pll> points;
map<pll, int> mp;

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

vector<pll> convex_hull()
{
    vector<pll> vt;

    first = {INF, INF};
    for (auto i : points)
        first = min(i, first);
    vt.push_back(first);

    sort(points.begin(), points.end(), [&](const pll &a, const pll &b) { return converter(a) < converter(b); });

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

map<pll, int> ans;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pll> save;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        save.push_back({x, y});
        points.push_back({x, y});
    }

    int cnt = 0;

    while (1)
    {
        auto vt = convex_hull();

        //cout << "convex\n";
        //for (auto [x, y] : vt)
        //    cout << x << " " << y << "\n";

        if (vt.size() <= 2)
            break;

        cnt++;
        for (auto i : vt)
            ans[i] = cnt;

        vector<pair<pll, pll>> edges;
        edges.push_back({vt[0], vt.back()});
        for (int i = 1; i < vt.size(); i++)
            edges.push_back({vt[i], vt[i - 1]});

        points.clear();
        for (auto i : save)
        {
            if (ans[i])
                continue;
            points.push_back(i);
            /*  
            bool flag = true;
            for (auto j : edges)
            {
                if (j.first != i && j.second != i && is_intersect(j, {i, i}))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                //cout << i.first << " <-> " << i.second << '\n';
                points.push_back(i);
            }
            */
        }
    }

    for (auto i : save)
    {
        cout << ans[i] << " ";
    }
    cout << '\n';
}