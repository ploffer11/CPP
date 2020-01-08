#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
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
        tree.resize(4 * n, INF);
    }

    void update_idx(int i, int s, int e, int idx, int diff)
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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    using t = tuple<int, int, int>;

    int n;
    cin >> n;

    vector<t> vt(n, t(-1, -1, -1));
    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        auto [a, b, c] = vt[--x];
        vt[x] = {i, b, c};
    }

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        auto [a, b, c] = vt[--x];
        vt[x] = {a, i, c};
    }

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        auto [a, b, c] = vt[--x];
        vt[x] = {a, b, i};
    }

    sort(vt.begin(), vt.end());

    ll ans = 0;
    for (auto [a, b, c] : vt)
    {
        if (Tree.query(1, 1, n, 1, b) > c)
            ans++;

        Tree.update_idx(1, 1, n, b, c);
    }

    cout << ans;
}