#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
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

char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}

int readInt()
{
    int ret = 0, flg = 1;
    char now = read();

    while (isspace(now))
        now = read();
    if (now == '-')
        flg = -1, now = read();
    while (now >= 48 && now <= 57)
    {
        ret = ret * 10 + now - 48;
        now = read();
    }
    return ret * flg;
}
class FenwickTree
{
private:
    int n;
    vector<ll> tree;

    ll _query(int idx)
    {
        ll ret = 0;
        while (idx)
        {
            ret += tree[idx];
            idx -= (-idx & idx);
        }
        return ret;
    }

public:
    FenwickTree(int n) : n(n)
    {
        tree.resize(n + 10, 0);
    }

    void update(int idx, ll diff)
    {
        while (idx <= n)
        {
            tree[idx] += diff;
            idx += (-idx & idx);
        }
    }

    ll query(int l, int r)
    {
        return _query(r) - _query(l - 1);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n = readInt(), m = readInt();
    SegmentTree tree(n);

    while (m--)
    {
        int x, y, z;
        x = readInt();
        y = readInt();
        z = readInt();
        if (x == 0)
            cout << tree.query(1, 1, n, min(y, z), max(y, z)) << "\n";
        else
            tree.update_idx(1, 1, n, y, z);
    }
}