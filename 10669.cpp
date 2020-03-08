#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 1001;

pii operator+(const pii &x, const pii &y)
{
    return {x.first + y.first, x.second + y.second};
}

struct Node
{
    pii sum, lsum, rsum, msum;

    Node()
    {
        sum.second = -1;
        lsum.second = -1;
        rsum.second = -1;
        msum.second = -1;
    }

    Node(pii &a, pii &b, pii &c, pii &d) : sum(a), lsum(b), rsum(c), msum(d) {}

    Node operator*(const Node &R)
    {
        auto L = *this;
        pii a = L.sum + R.sum;
        pii b = max(L.lsum, L.sum + R.lsum);
        pii c = max(R.rsum, R.sum + L.rsum);
        pii d = max(L.rsum + R.lsum, max(L.msum, R.msum));
        return {a, b, c, d};
    }

    void operator+=(const ll diff)
    {
        sum.first += diff;
        lsum.first += diff;
        rsum.first += diff;
        msum.first += diff;
    }
};

class SegmentTree
{
private:
    vector<Node> tree;

public:
    SegmentTree(int n) : tree(4 * (n + 1), Node()) { init(1, 0, n); }

    void init(int i, int s, int e)
    {
        if (s == e)
            return;
        tree[i].sum.second = -(e - s + 1);
        init(2 * i, s, (s + e) / 2);
        init(2 * i + 1, (s + e) / 2 + 1, e);
    }

    void update(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        if (s == e)
        {
            tree[i] += diff;
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
            return Node();
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return query(2 * i, s, m, l, r) * query(2 * i + 1, m + 1, e, l, r);
        }
    }
};

vector<pii> xofy[1005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    char z;
    int n;
    cin >> n;
    for (int i = 0, x, y; i < n; i++)
    {
        cin >> x >> y >> z;
        if (z == 'H')
            xofy[y].push_back({x, 1});
        else
            xofy[y].push_back({x, -1000});
    }

    pii ans = {1, 0};
    for (int i = 0; i <= 1000; i++)
    {
        SegmentTree tree(1000);
        for (int j = i; j <= 1000; j++)
        {
            for (auto [x, d] : xofy[j])
                tree.update(1, 0, 1000, x, d);

            auto node = tree.query(1, 0, 1000, 0, 1000);
            auto [msum, len] = node.msum;

            ans = max(ans, {msum, -((j - i) * (-len - 1))});
        }
    }
    cout << ans.first << "\n"
         << -ans.second;
}