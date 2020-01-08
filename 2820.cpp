#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

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

    void update_idx(int i, int s, int e, int idx, ll diff)
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
    int kth(int i, int s, int e, ll sum)
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

int s[500005], e[500005];
int money[500005];
int cnt;
vector<int> adj[500005];

void dfs(int from)
{
    s[from] = ++cnt;
    for (auto to : adj[from])
        if (!s[to])
            dfs(to);
    e[from] = cnt;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    SegmentTree Tree(n + 1);

    cin >> money[1];

    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> money[i] >> x;
        adj[x].push_back(i);
    }

    dfs(1);

    while (m--)
    {
        char a;
        int b, c;

        cin >> a;

        if (a == 'p')
        {
            cin >> b >> c;
            if (s[b] + 1 <= e[b])
                Tree.update_range(1, 1, n, s[b] + 1, e[b], c);
        }

        else
        {
            cin >> b;
            cout << money[b] + Tree.query(1, 1, n, s[b], s[b]) << "\n";
        }
    }
}