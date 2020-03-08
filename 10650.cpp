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

class MaxSegmentTree
{
private:
    vector<ll> tree;

public:
    MaxSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) >> 1;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

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
        tree.resize(4 * (n + 1), 0);
        lazy.resize(4 * (n + 1), 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) >> 1;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update_range(int i, int s, int e, int l, int r, ll diff)
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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
    int kth(int i, int s, int e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        int m = (s + e) >> 1;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

int X[100005], Y[100005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    SegmentTree tree1(n);
    MaxSegmentTree tree2(n);

    auto d = [&](int i, int j) { return abs(X[i] - X[j]) + abs(Y[i] - Y[j]); };
    auto u1 = [&](int i) {
        if (1 <= i && i <= n - 1)
            tree1.update_idx(1, 1, n, i, d(i, i + 1));
    };
    auto u2 = [&](int i) {
        for (int j = i - 1; j <= i + 1; j++)
        {
            if (2 <= j && j <= n - 1)
            {
                tree2.update_idx(1, 1, n, j, d(j - 1, j) + d(j, j + 1) - d(j - 1, j + 1));
            }
        }
    };

    for (int i = 1; i <= n; i++)
        cin >> X[i] >> Y[i];

    for (int i = 1; i <= n - 1; i++)
    {
        u1(i);
        u2(i);
    }

    while (q--)
    {
        char w;
        int x, y, z;
        cin >> w;
        if (w == 'Q')
        {
            cin >> x >> y;
            if (x == y)
                cout << "0\n";
            else if (y - x == 1)
                cout << d(x, y) << "\n";
            else
            {
                cout << tree1.query(1, 1, n, x, y - 1) - tree2.query(1, 1, n, x + 1, y - 1) << "\n";
            }
        }

        else
        {
            cin >> x >> y >> z;
            X[x] = y;
            Y[x] = z;
            u1(x), u1(x - 1);
            u2(x);
        }
    }
}