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
        update_lazy(i, s, e);
        if (s == e)
            return s;
        int m = (s + e) / 2;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

int cnt[300'005];
int s[300'005], e[300'005];
vector<int> num[300'005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(s, 0x3f, sizeof(s));
    memset(e, -1, sizeof(e));

    vector<int> arr;
    int t;
    cin >> t;
    while (t--)
    {
        int ans = 0;
        int n;
        cin >> n;
        SegmentTree Tree(n);
        arr.resize(n, 0);

        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            s[arr[i]] = min(s[arr[i]], i);
            e[arr[i]] = max(e[arr[i]], i);
            num[arr[i]].push_back(i);
            Tree.update_idx(1, 0, n - 1, i, 1);
        }

        for (int i = 1; i <= n; i++)
        {
            if (num[i].size())
            {
                for (auto j : num[i])
                    Tree.update_idx(1, 0, n - 1, j, -1);

                int q = Tree.query(1, 0, n - 1, s[i], e[i]);

                if (q)
                    ans++;
            }
        }

        for (auto i : arr)
        {
            s[i] = 0x3f3f3f3f;
            e[i] = -1;
            num[i].clear();
        }

        cout << ans << "\n";
    }
}