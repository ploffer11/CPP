#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
// #define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
// const int MAX = -1;

class OfflineLiChaoTree
{
private:
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

    vector<LiChaoTree> tree;
    vector<tuple<int, int, ll, ll>> q;
    vector<ll> ans;
    int q_idx;

    void insert(int i, int s, int e, int l, int r, pll value)
    {
        if (r < s || e < l)
            return;

        if (l <= s && e <= r)
        {
            tree[i].add_line({value.first, value.second});
            return;
        }

        int m = (s + e) >> 1;
        insert(2 * i, s, m, l, r, value);
        insert(2 * i + 1, m + 1, e, l, r, value);
    }

    ll query(int i, int s, int e, int idx, ll x)
    {
        if (!(s <= idx && idx <= e))
            return -INF;

        if (s == e)
            return tree[i].query(x);

        int m = (s + e) >> 1;
        return max({tree[i].query(x), query(2 * i, s, m, idx, x), query(2 * i + 1, m + 1, e, idx, x)});
    }

public:
    OfflineLiChaoTree(int q) : q_idx(0), tree(4 * q + 10), q(q + 10, {-1, -1, -1, -1}) {}

    int add_line(ll a, ll b)
    {
        q_idx++;
        q[q_idx] = {q_idx, -1, a, b};
        return q_idx;
    }

    void delete_line(int i)
    {
        q_idx++;
        auto &x = get<1>(q[i]);
        x = q_idx;
    }

    void query(ll x)
    {
        q_idx++;
        q[q_idx] = {0, q_idx, x, 0};
    }

    // return -INF if empty
    vector<ll> get_ans()
    {
        for (auto [a, b, c, d] : q)
        {
            if (a > 0)
            {
                insert(1, 1, q_idx, a, (b == -1 ? q_idx : b), {c, d});
            }
        }

        for (auto [a, idx, x, _] : q)
            if (a == 0)
                ans.push_back(query(1, 1, q_idx, idx, x));

        return ans;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int q;
    cin >> q;

    OfflineLiChaoTree tree(q);

    for (int i = 1; i <= q; i++)
    {
        int a, b, c;
        cin >> a;
        if (a == 1)
        {
            cin >> b >> c;
            tree.add_line(b, c);
        }
        else if (a == 2)
        {
            cin >> b;
            tree.delete_line(b);
        }
        else
        {
            cin >> b;
            tree.query(b);
        }
    }

    for (auto i : tree.get_ans())
    {
        if (i == -INF)
            cout << "EMPTY\n";
        else
            cout << i << "\n";
    }
}