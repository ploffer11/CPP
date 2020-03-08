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
const int MAX = 100005;

class DynamicMinSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll v;
        Node() : l(0), r(0), v(0x3f3f3f3f3f3f3f3f) {}
    };
    vector<Node> tree;

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        if (s == e)
        {
            tree[i].v = min(tree[i].v, diff);
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
        tree[i].v = min(tree[tree[i].l].v, tree[tree[i].r].v);
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        if (i == 0 || e < l || s > r)
            return 0x3f3f3f3f3f3f3f3f;
        else if (l <= s && e <= r)
            return tree[i].v;
        else
        {
            ll m = (s + e) >> 1;
            return min(_query(tree[i].l, s, m, l, r), _query(tree[i].r, m + 1, e, l, r));
        }
    }

public:
    ll s, e;
    DynamicMinSegmentTree(int cap = 2000000)
    {
        tree.reserve(cap);
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 0;
        this->e = (ll)1e9 + 5;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }
};

using tt = tuple<ll, ll, ll, ll, int>;
vector<tt> vt, u;
ll dp[MAX];
pll p1[MAX], p2[MAX];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    // memset(dp, -1, sizeof(dp));
    DynamicMinSegmentTree tree(2000000);

    ll n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        p1[i] = {a, b};
        p2[i] = {c, d};
        vt.push_back({a, b, c, d, i});
        u.push_back({c, d, a, b, i});
    }

    tree.update_idx(0, 0);

    sort(vt.begin(), vt.end());
    sort(u.begin(), u.end());

    int j = 0;
    for (auto [x1, y1, x2, y2, idx] : vt)
    {
        while (j < m)
        {
            auto [X2, Y2, X1, Y1, idx2] = u[j];

            if (X1 == X2 && Y1 == Y2)
            {
                j++;
                continue;
            }

            if (X2 < x1 || (X2 == x1 && Y2 <= y1))
            {
                tree.update_idx(Y2, dp[idx2] - X2 - Y2);
                j++;
            }
            else
                break;
        }
        ll temp = tree.query(0, y1);
        dp[idx] = temp + x1 + y1;
    }

    ll ans = INF;
    for (int i = 1; i <= m; i++)
    {
        // cout << dp[i] << " ";
        ans = min(ans, dp[i] + 2 * n - p2[i].first - p2[i].second);
    }
    cout << ans;
}

// 84305774 : 4.out
// 10.in도 틀림