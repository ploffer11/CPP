#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll dp[100'005];

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

    ll query(int i, int s, int e)
    {
        update_lazy(i, s, e);

        if (tree[i] == 0)
            return dp[e - s + 1];

        if (tree[i] == e - s + 1)
            return 1;

        int m = (s + e) / 2;
        return (query(2 * i, s, m) * query(2 * i + 1, m + 1, e)) % MOD;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= 100'000; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;

    int n, m;
    cin >> n >> m;

    SegmentTree Tree(n);
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1)
        {
            Tree.update_range(1, 1, n, b, c, 1);
        }

        else if (a == 2)
        {
            Tree.update_range(1, 1, n, b, c, -1);
        }

        cout << Tree.query(1, 1, n) << " <- \n";
    }
}