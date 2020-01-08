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

    ll _kth(int i, ll s, ll e, ll sum)
    {
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

    ll kth(ll sum)
    {
        return _kth(1, s, e, sum);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    ll OFFSET = (ll)1 << 32;

    int t;
    cin >> t;
    while (t--)
    {
        DynamicSegmentTree Tree;
        int n;
        cin >> n;

        int cnt = 0;

        cout << (n / 2) + 1 << '\n';
        for (int i = 1; i <= n; i++)
        {
            ll x;
            cin >> x;
            Tree.update_idx(x + OFFSET, 1);
            if (i % 2 == 1)
            {
                int k = i / 2 + 1;
                cout << Tree.kth(k) - OFFSET << (++cnt % 10 == 0 ? '\n' : ' ');
            }
        }
        cout << '\n';
    }
}