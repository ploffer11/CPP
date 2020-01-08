#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

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

class MinSegmentTree
{
private:
    vector<ll> tree;

public:
    MinSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), INF);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = min(tree[i], diff);
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

vector<int> sol;
vector<tuple<int, int, int>> q;
vector<int> vt[200005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    MinSegmentTree tree(200005);
    MaxSegmentTree tree2(200005);

    int m, n, k, t;
    cin >> m >> n >> k >> t;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        sol.push_back(x);
    }

    for (int i = 1; i <= k; i++)
    {
        int l, r, d;
        cin >> l >> r >> d;
        q.push_back({r, l, d});
        tree.update_idx(1, 1, 200000, d, l);
        vt[r].push_back(d);
    }
    
    int ans = 0;

    sort(sol.begin(), sol.end());
    sort(q.begin(), q.end());
    reverse(q.begin(), q.end());

    int d_max = 0;
    for (int r = n; r >= 1; r--)
    {
        int idx = lower_bound(sol.begin(), sol.end(), d_max) - sol.begin();
        int can_save = m - idx;

        if (idx == m)
            continue;

        int sol_min = sol[idx];
        int l_min = tree.query(1, 1, 200000, sol_min + 1, 200000);

        ll time = (l_min - 1) + (r - l_min + 1) * 2 + (n + 2 - l_min);
        if (l_min == INF)
            time = n + 1;

        //cout << time << "\n";
        if (time <= t)
            ans = max(ans, can_save);

        for (auto d : vt[r])
            d_max = max(d_max, d);
    }

    cout << ans;
}