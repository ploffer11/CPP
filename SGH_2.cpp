#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class SegmentTree
{
private:
    vector<ll> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
    }

    void update_idx(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;

        if (s == e)
        {
            tree[i] += diff;
            return;
        }

        int m = (s + e) / 2;
        update_idx(2 * i, s, m, idx, diff);
        update_idx(2 * i + 1, m + 1, e, idx, diff);
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[i];

        int m = (s + e) / 2;
        return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
    }
};
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    SegmentTree even(n), odd(n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (i % 2 == 0)
            even.update_idx(1, 1, n, i, x);

        else
            odd.update_idx(1, 1, n, i, x);
    }

    while (m--)
    {
        int q, l, r;
        cin >> q >> l >> r;

        if (q == 1)
            cout << abs(odd.query(1, 1, n, l, r) - even.query(1, 1, n, l, r)) << '\n';
        else
        {
            if (l % 2 == 0)
                even.update_idx(1, 1, n, l, r);

            else
                odd.update_idx(1, 1, n, l, r);
        }
    }
}