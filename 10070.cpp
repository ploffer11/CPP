#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

pll operator*(pll &base, pll &add)
{
    auto [l1, r1] = base;
    auto [l2, r2] = add;

    if (l1 <= l2 && r2 <= r1)
        return {l2, r2};

    if (l2 <= l1 && r1 <= r2)
        return {l1, r1};

    if (l2 >= r1)
        return {l2, l2};

    if (r2 <= l1)
        return {r2, r2};

    if (l1 <= l2 && r1 <= r2)
        return {l2, r1};

    if (l2 <= l1 && r2 <= r1)
        return {l1, r2};

    return {-123456789, 123456789};
}
class SegmentTree
{
private:
    const pll INITIAL = {-INF, INF};
    vector<ll> tree;
    vector<pll> lazy;

    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != INITIAL && s != e)
        {
            lazy[2 * i] = lazy[2 * i] * lazy[i];
            lazy[2 * i + 1] = lazy[2 * i + 1] * lazy[i];
            lazy[i] = INITIAL;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, INITIAL);
    }

    void update_range(int i, int s, int e, int l, int r, pll diff)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] = lazy[i] * diff;
        }
        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
        }
    }

    ll query(int i, int s, int e, int idx)
    {
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return 0;
        else if (s == e)
        {
            auto [l, r] = lazy[i];

            //cout << idx << ": " << l << " ~ " << r << "\n";
            if (l <= 0 && 0 <= r)
                return 0;
            else if (0 < l)
                return l;
            else
                return r;
        }
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, idx) + query(2 * i + 1, m + 1, e, idx);
        }
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    SegmentTree Tree(n);

    while (m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a == 1)
            Tree.update_range(1, 0, n - 1, b, c, pll(d, INF));

        else
            Tree.update_range(1, 0, n - 1, b, c, pll(-INF, d));
    }

    for (int i = 0; i < n; i++)
        cout << Tree.query(1, 0, n - 1, i) << "\n";
}