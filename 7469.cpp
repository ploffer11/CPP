#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class MergeSortTree
{
private:
    vector<vector<ll>> tree;
    vector<ll> arr;

public:
    MergeSortTree(int n, vector<ll> vt)
    {
        tree.resize(4 * n);
        arr = vt;
        init(1, 1, n);
    }

    vector<ll> init(int i, int s, int e)
    {
        if (s == e)
            return tree[i] = {arr[s]};

        int m = (s + e) / 2;
        vector<ll> vt;
        vt.reserve(e - s + 1);
        for (auto i : init(2 * i, s, m))
            vt.push_back(i);
        for (auto i : init(2 * i + 1, m + 1, e))
            vt.push_back(i);

        sort(vt.begin(), vt.end());
        return tree[i] = vt;
    }

    int query(int i, int s, int e, int l, int r, int k)
    {
        if (s > r || e < l)
            return 0;

        if (l <= s && e <= r)
            return lower_bound(tree[i].begin(), tree[i].end(), k) - tree[i].begin();

        int m = (s + e) / 2;

        return query(2 * i, s, m, l, r, k) + query(2 * i + 1, m + 1, e, l, r, k);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<ll> arr(n + 1);

    arr[0] = -2 * INF;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    MergeSortTree Tree(n, arr);

    sort(arr.begin(), arr.end());
    while (m--)
    {
        int l, r, k;
        cin >> l >> r >> k;

        int s = -1'000'000'001, e = 1'000'000'001;
        while (s <= e)
        {
            int m = (s + e) / 2;
            auto q = Tree.query(1, 1, n, l, r, m);

            q++;

            if (q <= k)
                s = m + 1;
            else
                e = m - 1;
        }
        cout << e << '\n';
    }
}