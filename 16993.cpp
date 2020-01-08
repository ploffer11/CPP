#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

struct Node
{
    int sum, lsum, rsum, msum;
    Node operator*(const Node &R)
    {
        if (this->sum == -INF)
            return R;
        if (R.sum == -INF)
            return *this;

        auto L = *this;
        int a = L.sum + R.sum;
        int b = max(L.lsum, L.sum + R.lsum);
        int c = max(R.rsum, R.sum + L.rsum);
        int d = max(L.rsum + R.lsum, max(L.msum, R.msum));
        return {a, b, c, d};
    }

    Node operator+(const int x)
    {
        return {sum + x, lsum + x, rsum + x, msum + x};
    }
};

class SegmentTree
{
private:
    vector<Node> tree;

public:
    SegmentTree(int n) : tree(4 * (n + 1), {0, 0, 0, 0}) {}

    void update(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        if (s == e)
        {
            tree[i] = tree[i] + diff;
            return;
        }
        else
        {
            int m = (s + e) >> 1;
            update(2 * i, s, m, idx, diff);
            update(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] * tree[2 * i + 1];
        }
    }

    Node query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {-INF, -INF, -INF, -INF};
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return query(2 * i, s, m, l, r) * query(2 * i + 1, m + 1, e, l, r);
        }
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    SegmentTree tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        tree.update(1, 1, n, i, x);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << tree.query(1, 1, n, l, r).msum << "\n";
    }
}