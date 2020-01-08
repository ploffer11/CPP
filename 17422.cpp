#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
const ll INF = 12345678987654321;
const ll MOD = 1e9 + 7;
const ll MAX = 270000;

class SegmentTree
{
private:
    vector<ll> tree, lazy;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
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
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return -INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

SegmentTree Tree(MAX);
vector<ll> adj[MAX];
ll s[MAX], e[MAX], money[MAX], sum[MAX];
ll n, cnt;

ll dfs(ll a)
{
    s[a] = ++cnt;
    ll ret = 0;

    for (auto b : adj[a])
        ret = max(ret, dfs(b));

    e[a] = cnt;

    if (ret)
        Tree.update_idx(1, 1, MAX, a, money[a] + sum[adj[a][0]] + sum[adj[a][1]]);
    else
        Tree.update_idx(1, 1, MAX, a, money[a]);

    return sum[a] = ret + money[a];
}

ll update(int a, int i)
{
    if (!(s[a] <= s[i] && s[i] <= e[a]))
        return sum[a];

    ll ret = 0;
    for (auto b : adj[a])
        ret = max(ret, update(b, i));

    if (ret)
        Tree.update_idx(1, 1, MAX, a, money[a] + sum[adj[a][0]] + sum[adj[a][1]]);
    else
        Tree.update_idx(1, 1, MAX, a, money[a]);

    return sum[a] = ret + money[a];
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    ll depth = log2(n + 1);

    for (ll i = 1; i <= (1 << (depth - 1)) - 1; i++)
    {
        adj[i].push_back(2 * i);
        adj[i].push_back(2 * i + 1);
    }

    for (ll i = 1; i <= n; i++)
        cin >> money[i];

    dfs(1);
    cout << Tree.query(1, 1, MAX, 1, MAX) << '\n';

    ll q;
    cin >> q;

    while (q--)
    {
        ll x, y;
        cin >> x >> y;

        money[x] = y;
        update(1, x);

        cout << Tree.query(1, 1, MAX, 1, MAX) << '\n';
    }
}