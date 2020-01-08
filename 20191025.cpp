#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const ll INF = 1e15;
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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll n, s;
        cin >> n >> s;
        vector<pll> arr;
        SegmentTree Tree(n);

        for (int i = 0; i < n; i++)
        {
            ll a, b;
            cin >> a >> b;
            arr.push_back({a, b});
            s -= a;
            Tree.update_idx(1, 0, n - 1, i, a);
        }
        sort(arr.begin(), arr.end());
        arr.push_back({INF, INF});
        ll curM = INF;
        int mid = n / 2;
        ll ans = arr[mid].first;
        for (int i = mid; i < n; i++)
        {
            auto [l, r] = arr[i];
            curM = min(curM, r);
            ll x = min(curM, arr[i + 1].first);
            ll diff = x - l;

            if (s > (i - mid + 1) * diff)
            {
                arr[i].first = x;
                ans = x;
                s -= (i - mid + 1) * diff;
                Tree.update_range(1, 0, n - 1, mid, i, diff);
            }
            else
            {
                ans += s / (i - mid + 1);
                Tree.update_range(1, 0, n - 1, mid, i, s / (i - mid + 1));
                break;
            }
        }

        if (s == 0)
        {
            cout << ans << "\n";
            continue;
        }
        else
        {
            
        }
    }
}