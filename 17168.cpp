#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

class LiChaoTree
{
private:
    struct Line
    {
        int idx;
        ll a, b;
        Line(ll a, ll b, int idx = -1) : a(a), b(b), idx(idx) {}

        ll f(ll x)
        {
            return a * x + b;
        }
    };

    struct Node
    {
        int l, r;
        ll xl, xr;
        Line line;
    };

    vector<Node> tree;

public:
    ll s = -2e9, e = 2e9;
    LiChaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    void add_line(Line new_line, int i = 0)
    {
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;

        Line low = tree[i].line, high = new_line;

        if (low.f(xl) >= high.f(xl))
            swap(low, high);

        if (low.f(xr) <= high.f(xr))
        {
            tree[i].line = high;
            return;
        }

        else if (low.f(xm) <= high.f(xm))
        {
            tree[i].line = high;

            if (tree[i].r == -1)
            {
                tree[i].r = tree.size();
                tree.push_back({-1, -1, xm + 1, xr, Line(0, -INF)});
            }
            add_line(low, tree[i].r);
        }
        else
        {
            tree[i].line = low;
            if (tree[i].l == -1)
            {
                tree[i].l = tree.size();
                tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
            }
            add_line(high, tree[i].l);
        }
    }

    ll query(ll x, int i = 0)
    {
        if (i == -1)
            return -INF;
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm)
            return max(tree[i].line.f(x), query(x, tree[i].l));
        else
            return max(tree[i].line.f(x), query(x, tree[i].r));
    }

    Line query2(ll x, int i = 0)
    {
        if (i == -1)
            return Line(0, -INF);
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm)
        {
            Line line = query2(x, tree[i].l);
            if (line.f(x) > tree[i].line.f(x))
                return line;
            else
                return tree[i].line;
        }
        else
        {
            Line line = query2(x, tree[i].r);
            if (line.f(x) > tree[i].line.f(x))
                return line;
            else
                return tree[i].line;
        }
    }
};

ll sum_h, sum_wh;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    LiChaoTree tree;

    int n;
    cin >> n;

    vector<pll> box;
    for (int i = 1; i <= n; i++)
    {
        ll x, y;
        cin >> x >> y;
        box.push_back({max(x, y), min(x, y)});
        sum_h += max(x, y);
        sum_wh += x * y;
    }
    sort(box.begin(), box.end());

    auto [h, w] = box[0];
    tree.add_line({-h, w * h + h * sum_h - h * h});
    ll ans = -INF;
    for (int i = 1; i < box.size(); i++)
    {
        auto [h, w] = box[i];
        ans = max(ans, tree.query(h) - sum_wh + w * h);
        tree.add_line({-h, w * h + h * sum_h - h * h});
    }

    cout << ans;
}