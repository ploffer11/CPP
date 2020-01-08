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
};

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
            int m = (s + e) / 2;
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
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

const int MAX = 200005;
vector<tuple<int, int, int>> query[MAX];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    SegmentTree Tree(MAX);
    MaxSegmentTree Tree2(MAX);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        Tree.update_range(1, 1, MAX, l, r, 1);
        query[l].push_back({l, -r, i});
    }

    for (int i = 0; i < MAX; i++)
    {
        Tree2.update_idx(1, 1, MAX, i, Tree.query(1, 1, MAX, i, i));
        sort(query[i].begin(), query[i].end());
    }

    vector<int> ans;
    for (int i = 1; i < MAX; i++)
    {
        for (auto [l, r, j] : query[i])
        {
            if (Tree2.query(1, 1, MAX, l, -r) > k)
            {
                ans.push_back(j);
                Tree.update_range(1, 1, MAX, l, -r, -1);
            }
            else
                break;
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto i : ans)
        cout << i << " ";
}