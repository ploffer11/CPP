#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;
const int N = 100005;
const int INF = 987654321;

class SegmentTree
{
private:
    vector<ll> tree, lazy;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update(int i, int s, int e, int l, int r, int diff)
    {
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
            lazy[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update(2 * i, s, m, l, r, diff);
            update(2 * i + 1, m + 1, e, l, r, diff);
        }
    }

    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += lazy[i] * (e - s + 1);
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    ll query(int i, int s, int e, int idx)
    {
        update_lazy(i, s, e);

        if (!(s <= idx && idx <= e))
            return 0;
        else if (s == e)
            return tree[i];

        int m = (s + e) / 2;
        return query(2 * i, s, m, idx) + query(2 * i + 1, m + 1, e, idx);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Tree.update(1, 1, n, i, i, x);
    }

    int q;
    cin >> q;

    while (q--)
    {
        int query;
        cin >> query;
        if (query == 1)
        {
            int l, r, d;
            cin >> l >> r >> d;
            Tree.update(1, 1, n, l, r, d);
        }
        else
        {
            int x;
            cin >> x;
            cout << Tree.query(1, 1, n, x) << '\n';
        }
    }
}