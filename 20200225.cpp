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

class DynamicSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll value;
        Node() : l(0), r(0), value(0) {}
    };
    vector<Node> tree;

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        if (s == e)
        {
            tree[i].value += diff;
            return;
        }

        ll m = (s + e) >> 1;
        if (idx <= m)
        {
            if (tree[i].l == 0)
            {
                tree[i].l = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].l, s, m, idx, diff);
        }
        else
        {
            if (tree[i].r == 0)
            {
                tree[i].r = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].r, m + 1, e, idx, diff);
        }
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        if (i == 0 || e < l || s > r)
            return 0;
        else if (l <= s && e <= r)
            return tree[i].value;
        else
        {
            ll m = (s + e) >> 1;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

    ll _kth(int i, ll s, ll e, ll sum)
    {
        if (s == e)
            return s;
        ll m = (s + e) >> 1;
        if (tree[tree[i].l].value < sum)
            return _kth(tree[i].r, m + 1, e, sum - tree[tree[i].l].value);
        else
            return _kth(tree[i].l, s, m, sum);
    }

public:
    ll s, e;
    DynamicSegmentTree(int cap)
    {
        tree.reserve(cap);
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = -(ll)1e10;
        this->e = (ll)1e10;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }

    ll kth(ll sum)
    {
        return _kth(1, s, e, sum);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    DynamicSegmentTree tree1(1000000), tree2(1000000);

    int n;
    cin >> n;
    vector<pll> vt;
    vector<ll> X(n), V(n);
    for (int i = 0; i < n; i++)
        cin >> X[i];
    for (int i = 0; i < n; i++)
    {
        cin >> V[i];
        vt.push_back({X[i], V[i]});
    }

    sort(vt.begin(), vt.end());
    reverse(vt.begin(), vt.end());

    ll ans = 0;
    for (auto [x, v] : vt)
    {
        ll cnt = tree1.query(v, 1e10 - 5);
        ll sum = tree2.query(v, 1e10 - 5);

        ans += sum - cnt * x;
        tree1.update_idx(v, 1);
        tree2.update_idx(v, x);
    }
    cout << ans;
}