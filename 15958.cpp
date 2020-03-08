#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

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

ll L[250005], R[250005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<pll> point;
    vector<ll> X, Y;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        point.push_back({x, y});
    }

    for (int i = 0; i < n - 1; i++)
    {
        auto [x1, y1] = point[i];
        auto [x2, y2] = point[i + 1];
        if (i % 2 == 0)
        {
            X.push_back(x1);
        }
        else
        {
            Y.push_back(y1);
        }
    }

    // height, x, line idx
    using tt = tuple<ll, ll, int>;
    {
        OfflineLiChaoTree tree(750000);
        priority_queue<tt, vector<tt>, less<tt>> pq;

        int idx = tree.add_line(Y[0], -X[0] * Y[0]);
        pq.push({Y[0], X[0], idx});

        for (int i = 1; i < X.size(); i++)
        {
            tree.query(X[i]);
            // cout << i << " -> " << get<0>(pq.top()) << "\n";
            if (i != X.size() - 1)
            {
                ll min_x = X[i];
                while (!pq.empty() && get<0>(pq.top()) >= Y[i])
                {
                    auto [y, x, idx] = pq.top();
                    pq.pop();
                    tree.delete_line(idx);
                    min_x = min(min_x, x);
                }
                idx = tree.add_line(Y[i], -min_x * Y[i]);
                pq.push({Y[i], min_x, idx});
            }
        }

        int i = 1;
        for (auto j : tree.get_ans())
            L[i++] = j;
    }
    {
        OfflineLiChaoTree tree2(750000);
        priority_queue<tt, vector<tt>, less<tt>> pq2;
        int idx = tree2.add_line(-Y.back(), X.back() * Y.back());
        pq2.push({Y.back(), X.back(), idx});

        for (int i = X.size() - 2; i >= 0; i--)
        {
            tree2.query(X[i]);
            if (i != 0)
            {
                ll max_x = X[i];
                while (!pq2.empty() && get<0>(pq2.top()) >= Y[i - 1])
                {
                    auto [y, x, idx] = pq2.top();
                    pq2.pop();
                    tree2.delete_line(idx);
                    max_x = max(max_x, x);
                }
                idx = tree2.add_line(-Y[i - 1], max_x * Y[i - 1]);
                pq2.push({Y[i - 1], max_x, idx});
            }
        }

        int i = X.size() - 2;
        for (auto j : tree2.get_ans())
            R[i--] = j;
    }

    ll ans = 0;
    for (int i = 0; i < X.size(); i++)
    {
        // cout << L[i] << " " << R[i] << "\n";
        ans = max(ans, L[i] + R[i]);
    }

    cout << ans;
}
