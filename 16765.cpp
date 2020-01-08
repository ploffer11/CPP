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
    vector<ll> tree;

public:
    SegmentTree(int n)
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
            return -INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

ll dp[10005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Tree.update_idx(1, 1, n, i, x);
    }

    for (int i = 1; i <= k; i++)
    {
        dp[i] = Tree.query(1, 1, n, 1, i) * i;
        //cout << dp[i] << " ";
    }

    for (int i = k + 1; i <= n; i++)
    {
        for (int j = i - k; j <= i - 1; j++)
        {
            dp[i] = max(dp[i], dp[j] + Tree.query(1, 1, n, j + 1, i) * (i - j));
        }
        //cout << dp[i] << " ";
    }

    cout << dp[n];
}