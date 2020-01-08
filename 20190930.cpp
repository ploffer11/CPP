#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;

// b->a b->c
pll get_ans(pll a, pll b, pll c)
{
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    auto [x3, y3] = c;

    pll vt1 = {x1 - x2, y1 - y2};
    pll vt2 = {x3 - x2, y3 - y2};

    if (vt1.first * vt2.first + vt1.second * vt2.second == 0)
    {
        return {
            b.first + vt1.first + vt2.first,
            b.second + vt1.second + vt2.second};
    }

    return {-INF, -INF};
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int a, b;
    cin >> a >> b;
    pll _1 = {a, b};
    cin >> a >> b;
    pll _2 = {a, b};
    cin >> a >> b;
    pll _3 = {a, b};

    auto [x1, y1] = get_ans(_1, _2, _3);

    auto [x2, y2] = get_ans(_2, _1, _3);

    auto [x3, y3] = get_ans(_1, _3, _2);

    if (x1 != -INF)
    {
        cout << x1 << " " << y1;
        return 0;
    }
    if (x2 != -INF)
    {
        cout << x2 << " " << y2;
        return 0;
    }
    if (x3 != -INF)
    {
        cout << x3 << " " << y3;
        return 0;
    }
}