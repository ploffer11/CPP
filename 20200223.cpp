#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 500'005;

using tt = tuple<int, ll>;
class MaxSegmentTree
{
private:
    vector<tt> tree;

public:
    MaxSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), {-INF, -INF});
    }

    void update_idx(int i, int s, int e, int idx, tt diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) >> 1;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    tt query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {-INF, -INF};
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

int height[MAX];

ll D1[MAX], D2[MAX];
int arr[MAX];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<pii> vt, vt2;

    int n;
    cin >> n;

    MaxSegmentTree tree(n), tree2(n);

    for (int i = 1; i <= n; i++)
    {
        cin >> height[i];
        arr[i] = height[i];
        vt.push_back({height[i], i});
        vt2.push_back({height[i], -i});
    }

    sort(vt.begin(), vt.end());
    sort(vt2.begin(), vt2.end());

    for (auto [value1, idx1] : vt)
    {
        auto [idx2, value2] = tree.query(1, 1, n, 1, idx1 - 1);

        if (value2 == -INF)
        {
            D1[idx1] = value1 * idx1;
            tree.update_idx(1, 1, n, idx1, {idx1, D1[idx1]});
        }
        else
        {
            D1[idx1] = value2 + (idx1 - idx2) * value1;
            tree.update_idx(1, 1, n, idx1, {idx1, D1[idx1]});
        }
    }

    for (auto [value1, idx1] : vt2)
    {
        idx1 = -idx1;

        auto [idx2, value2] = tree2.query(1, 1, n, idx1 + 1, n);
        idx2 = -idx2;

        if (value2 == -INF)
        {
            D2[idx1] = value1 * (n - idx1 + 1);
            tree2.update_idx(1, 1, n, idx1, {-idx1, D2[idx1]});
        }
        else
        {
            D2[idx1] = value2 + value1 * (idx2 - idx1);
            tree2.update_idx(1, 1, n, idx1, {-idx1, D2[idx1]});
        }
    }

    pair<ll, int> ans = {-INF, -INF};

    ans = max(ans, {D1[n], n});
    ans = max(ans, {D2[1], 1});
    for (int i = 1; i <= n - 1; i++)
    {
        ans = max(ans, {D1[i] + D2[i + 1], i});
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << D1[i] << " ";
    // }
    // cout << "\n";
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << D2[i] << " ";
    // }
    // cout << "\n";

    int i = ans.second;
    int top = height[i];
    for (int j = i - 1; j >= 1; j--)
    {
        top = min(height[j], top);
        arr[j] = top;
    }

    top = height[i];
    for (int j = i + 1; j <= n; j++)
    {
        top = min(height[j], top);
        arr[j] = top;
    }

    for (int i = 1; i <= n; i++)
        cout << arr[i] << " ";
}