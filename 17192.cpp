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

ll arr[405];
ll dp[405][405], s[405][405];
ll psum[405];

ll sum(int l, int r)
{
    return psum[r] - psum[l - 1];
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    MaxSegmentTree Tree(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        psum[i] = psum[i - 1] + arr[i];
        Tree.update_idx(1, 1, n, i, arr[i]);
    }

    s[1][0] = 1;
    dp[1][0] = 0;
    for (int i = 2; i <= n; i++)
    {
        s[i][0] = 1;
        dp[i][0] = i * Tree.query(1, 1, n, 1, i) - sum(1, i);
    }

    for (int i = 1; i <= k; i++)
        s[0][i] = 1;

    for (int j = 1; j <= k; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            ll x = Tree.query(1, 1, n, s[i - 1][j], i - 1) * (i - s[i - 1][j]) - sum(s[i - 1][j], i - 1);
            dp[i][j] = dp[i - 1][j] - x + Tree.query(1, 1, n, s[i - 1][j], i) * (i - s[i - 1][j] + 1) - sum(s[i - 1][j], i);
            s[i][j] = s[i - 1][j];
            for (int l = 1; l <= i - 1; l++)
            {
                ll y = dp[l][j - 1] + (Tree.query(1, 1, n, l + 1, i) * (i - l)) - sum(l + 1, i);
                if (y < dp[i][j])
                {
                    s[i][j] = l + 1;
                    dp[i][j] = y;
                }
            }
            //cout << i << " " << j << " " << dp[i][j] << "\n";
        }
    }   
    cout << dp[n][k];
}