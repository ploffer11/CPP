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
    int kth(int i, int s, int e, int sum)
    {
        if (s == e)
            return s;
        int m = (s + e) / 2;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, x, y;

        vector<int> vx, vy;
        vector<int> cx, cy;

        cin >> n;

        SegmentTree Tree(n);

        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            vx.push_back(x);
            vy.push_back(y);
        }

        cx = vx;
        cy = vy;

        sort(cx.begin(), cx.end());
        sort(cy.begin(), cy.end());
        cx.resize(unique(cx.begin(), cx.end()) - cx.begin());
        cy.resize(unique(cy.begin(), cy.end()) - cy.begin());

        vector<pii> vt;
        for (int i = 0; i < n; i++)
        {
            vx[i] = (int)(lower_bound(cx.begin(), cx.end(), vx[i]) - cx.begin()) + 1;
            vy[i] = (int)(lower_bound(cy.begin(), cy.end(), vy[i]) - cy.begin()) + 1;
            vt.push_back({vy[i], -vx[i]});
        }

        sort(vt.begin(), vt.end());

        ll ans = 0;

        for (auto [y, x] : vt)
        {
            ans += Tree.query(1, 1, n, -x, n);
            Tree.update_idx(1, 1, n, -x, 1);
        }

        cout << ans << "\n";
    }
}