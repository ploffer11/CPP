#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

struct Node
{
    ll sum, lsum, rsum, msum;
    Node operator*(const Node &R)
    {
        if (this->sum == -INF)
            return R;
        if (R.sum == -INF)
            return *this;

        auto L = *this;
        ll a = L.sum + R.sum;
        ll b = max(L.lsum, L.sum + R.lsum);
        ll c = max(R.rsum, R.sum + L.rsum);
        ll d = max(L.rsum + R.lsum, max(L.msum, R.msum));
        return {a, b, c, d};
    }

    Node operator+(const ll x)
    {
        if (this->sum == -INF)
            return {x, x, x, x};
        else
            return {sum + x, lsum + x, rsum + x, msum + x};
    }
};

class SegmentTree
{
private:
    vector<Node> tree;

public:
    SegmentTree(int n) : tree(4 * (n + 1), {-INF, -INF, -INF, -INF}) {}

    void update(int i, int s, int e, int idx, ll diff)
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

vector<pii> xofy[3005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<int> X, Y;
    vector<tuple<int, int, int>> point;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
        point.push_back({x, y, 0});
    }

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
        point.push_back({x, y, 1});
    }

    int s, b;
    cin >> s >> b;

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());
    Y.resize(unique(Y.begin(), Y.end()) - Y.begin());

    for (auto [x, y, z] : point)
    {
        int x2 = lower_bound(X.begin(), X.end(), x) - X.begin();
        int y2 = lower_bound(Y.begin(), Y.end(), y) - Y.begin();
        xofy[y2].push_back({x2, (z == 0 ? s : -b)});
    }

    ll ans = -INF;

    for (int i = 0; i < Y.size(); i++)
    {
        SegmentTree tree(X.size());
        for (int j = i; j < Y.size(); j++)
        {
            for (auto [x, z] : xofy[j])
                tree.update(1, 0, X.size(), x, z);

            ans = max(ans, tree.query(1, 0, X.size(), 0, X.size()).msum);
        }
    }
    cout << ans;
}