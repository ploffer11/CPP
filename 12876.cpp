#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
// const int MAX = -1;

// const int INF = 2e9 + 10;
class OfflineLiChaoTree
{
private:
    class LiChaoTree
    {
    private:
        struct Line
        {
            ll a, b;
            Line(ll a, ll b) : a(a), b(b) {}

            ll f(ll x)
            {
                return (ll)a * x + b;
            }
        };

        struct Node
        {
            int l, r;
            int xl, xr;
            Line line;
        };

        vector<Node> tree;

    public:
        int s = -2e9, e = 2e9;
        LiChaoTree()
        {
            tree.push_back({-1, -1, s, e, Line(0, -INF)});
        }

        void add_line(Line new_line, int i = 0)
        {
            int xl = tree[i].xl, xr = tree[i].xr;
            int xm = ((ll)xl + xr) >> 1;

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
            int xl = tree[i].xl, xr = tree[i].xr;
            int xm = ((ll)xl + xr) >> 1;
            if (x <= xm)
                return max(tree[i].line.f(x), query(x, tree[i].l));
            else
                return max(tree[i].line.f(x), query(x, tree[i].r));
        }

        Line query2(ll x, int i = 0)
        {
            if (i == -1)
                return Line(0, -INF);
            int xl = tree[i].xl, xr = tree[i].xr;
            int xm = ((ll)xl + xr) >> 1;
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
    vector<pair<int, ll>> q2;
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

        int m = ((ll)s + e) >> 1;
        insert(2 * i, s, m, l, r, value);
        insert(2 * i + 1, m + 1, e, l, r, value);
    }

    ll query(int i, int s, int e, int idx, ll x)
    {
        if (!(s <= idx && idx <= e))
            return -INF;

        if (s == e)
            return tree[i].query(x);

        int m = ((ll)s + e) >> 1;
        return max({tree[i].query(x), query(2 * i, s, m, idx, x), query(2 * i + 1, m + 1, e, idx, x)});
    }

public:
    OfflineLiChaoTree(int q) : q_idx(0), tree(4 * q) {}

    int add_line(ll a, ll b)
    {
        q.push_back({++q_idx, -1, a, b});
        return q.size() - 1;
    }

    void delete_line(int i)
    {
        get<1>(q[i]) = ++q_idx;
    }

    void query(ll x)
    {
        q2.push_back({++q_idx, x});
    }

    vector<ll> get_ans()
    {
        for (auto [l, r, a, b] : q)
            insert(1, 1, q_idx, l, (r == -1 ? q_idx : r), {a, b});

        for (auto [idx, x] : q2)
            ans.push_back(query(1, 1, q_idx, idx, x));

        return ans;
    }
};

int save[300005];
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
            int idx = tree.add_line(b, c);
            save[i] = idx;
        }
        else if (a == 2)
        {
            cin >> b;
            tree.delete_line(save[b]);
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