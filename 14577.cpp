#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

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

    void update_lazy(int i, ll s, ll e)
    {
        if (tree[i].lazy)
        {
            tree[i].value += (e - s + 1) * tree[i].lazy;
            if (s != e)
            {
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

                tree[tree[i].l].lazy += tree[i].lazy;
                tree[tree[i].r].lazy += tree[i].lazy;
            }
            tree[i].lazy = 0;
        }
    }

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        //update_lazy(i, s, e);
        if (s == e)
        {
            tree[i].value += diff;
            return;
        }

        ll m = (s + e) / 2;
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

    void _update_range(int i, ll s, ll e, ll l, ll r, ll diff)
    {
        update_lazy(i, s, e);
        if (e < l || s > r)
            return;

        if (l <= s && e <= r)
        {
            tree[i].lazy += diff;
            update_lazy(i, s, e);
            return;
        }

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
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        //update_lazy(i, s, e);
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

    ll _kth(int i, ll s, ll e, ll sum)
    {
        //cout << i << " " << s << " " << e << " " << endl;
        if (s == e)
            return s;
        ll m = (s + e) / 2;
        if (tree[tree[i].l].value < sum)
            return _kth(tree[i].r, m + 1, e, sum - tree[tree[i].l].value);
        else
            return _kth(tree[i].l, s, m, sum);
    }

public:
    ll s, e;
    DynamicSegmentTree()
    {
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 0;
        this->e = (ll)1e18 + 5;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }

    void update_range(ll l, ll r, ll diff)
    {
        _update_range(1, s, e, l, r, diff);
    }

    ll kth(ll sum)
    {
        return _kth(1, s, e, sum);
    }
};

ll snow[100005];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    DynamicSegmentTree Tree;

    ll n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> snow[i];
        Tree.update_idx(snow[i], 1);
    }

    while (m--)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int i, x;
            cin >> i >> x;
            Tree.update_idx(snow[i], -1);
            Tree.update_idx(snow[i] + x, 1);
            snow[i] += x;
        }
        else if (q == 2)
        {
            int i, x;
            cin >> i >> x;
            Tree.update_idx(snow[i], -1);
            Tree.update_idx(snow[i] - x, 1);
            snow[i] -= x;
        }
        else if (q == 3)
        {
            ll l, r;
            cin >> l >> r;
            cout << Tree.query(l, r) << '\n';
        }
        else
        {
            int t;
            cin >> t;
            cout << Tree.kth(n - t + 1) << '\n';
        }
    }
}