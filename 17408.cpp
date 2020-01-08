#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 1987654321;
const int MOD = 1e9 + 7;

class SegmentTree
{
private:
    vector<pii> tree;

    pii f(pii a, pii b)
    {
        vector<int> vt;
        vt.push_back(a.first);
        vt.push_back(b.first);
        vt.push_back(a.second);
        vt.push_back(b.second);
        sort(vt.begin(), vt.end());
        return {vt[3], vt[2]};
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, {-INF, -INF});
    }

    void update_idx(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;

        if (s == e)
        {
            tree[i] = {diff, -INF};
            return;
        }

        int m = (s + e) / 2;
        update_idx(2 * i, s, m, idx, diff);
        update_idx(2 * i + 1, m + 1, e, idx, diff);
        tree[i] = f(tree[2 * i], tree[2 * i + 1]);
    }

    pii query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {-INF, -INF};

        if (l <= s && e <= r)
            return tree[i];

        int m = (s + e) / 2;
        return f(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Tree.update_idx(1, 1, n, i, x);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int x, l, r;
        cin >> x >> l >> r;
        if (x == 1)
            Tree.update_idx(1, 1, n, l, r);
        else
        {
            auto [a, b] = Tree.query(1, 1, n, l, r);
            //cout << a << " " << b << '\n';
            cout << a + b << "\n";
        }
    }
}