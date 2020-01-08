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
    vector<ll> tree, lazy;
    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += (e - s + 1) * lazy[i];
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update_idx(int i, int s, int e, int idx, int diff)
    {
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update_range(int i, int s, int e, int l, int r, int diff)
    {
        update_lazy(i, s, e);

        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] += diff;
            update_lazy(i, s, e);
        }

        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
};

ll star[100005];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> star[i];

    SegmentTree range_tree(n), idx_tree(n);
    int q;
    cin >> q;
    while (q--)
    {
        int m;
        cin >> m;
        if (m == 1)
        {
            int l, r;
            cin >> l >> r;
            range_tree.update_idx(1, 1, n, l, 1);
            range_tree.update_idx(1, 1, n, r + 1, -1);

            idx_tree.update_idx(1, 1, n, l, l);
            idx_tree.update_idx(1, 1, n, r + 1, -l);
        }

        else
        {
            int x;
            cin >> x;

            int cnt = range_tree.query(1, 1, n, 1, x);
            int sum = idx_tree.query(1, 1, n, 1, x);

            //cout << "cnt, sum: " << cnt << " " << sum << '\n';
            ll delta = 1LL * (x + 1) * cnt - sum;
            cout << star[x] + delta << '\n';
        }
    }
}