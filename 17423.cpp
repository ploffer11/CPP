#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int START = 0, END = 1;
const ll OFFSET = 1000000005;

class DynamicSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll value, lazy;
        Node() : l(0), r(0), value(0), lazy(0) {}
    };
    vector<Node> tree;

    void _update_range(int i, ll s, ll e, ll l, ll r, ll diff)
    {
        if (e < l || s > r)
            return;

        else if (l <= s && e <= r)
            tree[i].lazy += diff;

        else
        {
            ll m = (s + e) / 2;

            if (tree[i].l == 0)
            {
                tree[i].l = tree.size();
                tree.push_back(Node());
            }

            if (tree[i].r == 0)
            {
                tree[i].r = tree.size();
                tree.push_back(Node());
            }

            _update_range(tree[i].l, s, m, l, r, diff);
            _update_range(tree[i].r, m + 1, e, l, r, diff);
        }

        if (tree[i].lazy > 0)
            tree[i].value = e - s + 1;
        else if (s != e)
            tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
        else
            tree[i].value = 0;
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        if (i == 0 || e < l || s > r)
            return 0;
        else if (l <= s && e <= r)
            return tree[i].value;
        else
        {
            ll m = (s + e) / 2;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

public:
    ll s, e;
    DynamicSegmentTree()
    {
        tree.reserve(20000000);
        tree.push_back(Node());
        tree.push_back(Node());

        this->s = 0;
        this->e = (ll)OFFSET + 300'0000;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_range(ll l, ll r, ll diff)
    {
        _update_range(1, s, e, l, r, diff);
    }
};

int n;
ll sz[100005];
pii points[100005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> sz[i];

    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x + y, -x + y};
    }

    ll s = 0, e = (ll)1000000;
    while (s <= e)
    {
        ll volume = (s + e) / 2;
        vector<tuple<ll, ll, ll, ll>> query;
        DynamicSegmentTree Tree;

        long double total = 0;
        for (int i = 1; i <= n; i++)
        {
            auto [x, y] = points[i];
            query.push_back({(ll)x - sz[i] * volume, (ll)y - sz[i] * volume, (ll)y + sz[i] * volume, START});
            query.push_back({(ll)x + sz[i] * volume, (ll)y - sz[i] * volume, (ll)y + sz[i] * volume, END});
            total += (long double)(2 * sz[i] * volume) * (2 * sz[i] * volume);
        }

        sort(query.begin(), query.end());

        ll prev = get<0>(query[0]);
        long double area = 0;
        for (auto [x, y1, y2, q] : query)
        {
            area += (long double)(x - prev) * Tree.query(Tree.s, Tree.e);
            prev = x;

            if (q == START)
                Tree.update_range(y1 + OFFSET, y2 - 1 + OFFSET, 1);

            else
                Tree.update_range(y1 + OFFSET, y2 - 1 + OFFSET, -1);
        }

        if (area < total)
            e = volume - 1;
        else
            s = volume + 1;
    }
    cout << e << "\n";
}