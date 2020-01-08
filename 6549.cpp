#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

struct SegmentTree
{
    vector<pll> tree;
    vector<ll> arr;
    int n;
    SegmentTree()
    {
        cin >> n;

        if (n == 0)
            exit(0);

        tree.resize(4 * (n + 1));
        arr.resize(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        init(1, 0, n - 1);
    }

    void init(int i, int s, int e)
    {
        if (s == e)
        {
            tree[i] = pll(arr[s], s);
            return;
        }

        int m = (s + e) >> 1;
        init(2 * i, s, m);
        init(2 * i + 1, m + 1, e);
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    pll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {INF, INF};
        else if (l <= s && e <= r)
            return tree[i];

        int m = (s + e) >> 1;
        return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
    }

    ll get_ans(int l, int r)
    {
        //cout << l << " " << r << "\n";
        auto [min_h, min_i] = query(1, 0, n - 1, l, r);
        ll area = (r - l + 1) * min_h;

        if (min_i > l)
            area = max(area, get_ans(l, min_i - 1));
        if (min_i < r)
            area = max(area, get_ans(min_i + 1, r));

        return area;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    while (1)
    {
        SegmentTree tree;
        cout << tree.get_ans(0, tree.n - 1) << "\n";
    }
}