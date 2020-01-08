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
    vector<pii> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), pii(0, -1));
    }

    void update_idx(int i, int s, int e, int idx, pii diff)
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

    pii query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {-INF, -INF};
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

pii arr[100005];
int via[100005];
pii dp[100005];

void f(int x)
{
    if (via[x] != -1)
        f(via[x]);

    auto [a, b] = arr[x];
    cout << a << " " << b << "\n";
}

const int MAX = 100'0000;
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(via, -1, sizeof(via));

    vector<tuple<int, int, int>> q;

    int n;
    cin >> n;

    SegmentTree Tree(MAX);
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        arr[i] = {x, y};
        q.push_back({x, -y, i});
    }

    sort(q.begin(), q.end());

    for (auto [x, y, i] : q)
    {
        y = -y;

        auto [value, idx] = Tree.query(1, 1, MAX, y, MAX);

        //cout << x << " " << y << " " << i << " " << value << " " << idx << "\n";

        via[i] = idx;
        dp[i] = {value + 1, i};
        Tree.update_idx(1, 1, MAX, y, pii(value + 1, i));
    }

    pii ans = {-INF, -INF};

    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);

    cout << ans.first << endl;
    f(ans.second);
}