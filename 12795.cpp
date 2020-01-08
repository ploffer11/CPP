#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;

class LichaoTree
{
private:
    const ll INF = 1e18;
    struct Line
    {
        ll a, b;
        Line(ll a, ll b) : a(a), b(b) {}

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
    ll s = -2e12, e = 2e12;
    LichaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    void add_line(int i, Line new_line)
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
            add_line(tree[i].r, low);
        }
        else
        {
            tree[i].line = low;
            if (tree[i].l)
            {
                tree[i].l = tree.size();
                tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
            }
            add_line(tree[i].l, high);
        }
    }

    ll query(int i, ll x)
    {
        if (i == -1)
            return -INF;
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm)
            return max(tree[i].line.f(x), query(tree[i].l, x));
        else
            return max(tree[i].line.f(x), query(tree[i].r, x));
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    LichaoTree LT;
    int q;
    cin >> q;
    while (q--)
    {
        ll a, b, c;
        cin >> a >> b;
        if (a == 1)
        {
            cin >> c;
            LT.add_line(0, {b, c});
        }
        else
            cout << LT.query(0, b) << "\n";
    }
}