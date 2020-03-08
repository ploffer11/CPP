#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

class LiChaoTree
{
private:
    struct Line
    {
        ll a, b;
        Line(ll a, ll b) : a(a), b(b) {}

        ll f(ll x)
        {
            return a * x + b;
        }
    };

    struct Node
    {
        int l, r;
        int xl, xr;
        Line line;
    };

    vector<Node> tree;

public:
    int s = -2e9 - 1000, e = 2e9 + 1000;
    LiChaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    void add_line(Line new_line, int i = 0)
    {
        int xl = tree[i].xl, xr = tree[i].xr;
        int xm = (xl + xr) >> 1;

        Line low = tree[i].line, high = new_line;

        if (low.f(xl) >= high.f(xl))
            swap(low, high);

        if (low.f(xr) <= high.f(xr))
        {
            tree[i].line = high;
            return;
        }

        else if (low.f(xm) <= high.f(xm))
        {
            tree[i].line = high;
            if (tree[i].r == -1)
            {
                tree[i].r = tree.size();
                tree.push_back({-1, -1, xm + 1, xr, Line(0, -INF)});
            }
            add_line(low, tree[i].r);
        }
        else
        {
            tree[i].line = low;
            if (tree[i].l == -1)
            {
                tree[i].l = tree.size();
                tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
            }
            add_line(high, tree[i].l);
        }
    }

    ll query(ll x, int i = 0)
    {
        if (i == -1)
            return -INF;
        int xl = tree[i].xl, xr = tree[i].xr;
        int xm = (xl + xr) >> 1;
        if (x <= xm)
            return max(tree[i].line.f(x), query(x, tree[i].l));
        else
            return max(tree[i].line.f(x), query(x, tree[i].r));
    }
};

LiChaoTree tree[1048580];

class OfflineLiChaoTree
{
private:
    vector<tuple<int, int, ll, ll>> q;
    vector<pair<int, ll>> q2;
    vector<ll> ans;
    int q_idx;

    void insert(int i, int s, int e, int l, int r, pll value)
    {
        if (r < s || e < l)
            return;

        if (l <= s && e <= r)
        {
            tree[i].add_line({value.first, value.second});
            return;
        }

        int m = (s + e) >> 1;
        insert(2 * i, s, m, l, r, value);
        insert(2 * i + 1, m + 1, e, l, r, value);
    }

    ll query(int i, int s, int e, int idx, ll x)
    {
        if (!(s <= idx && idx <= e))
            return -INF;

        if (s == e)
            return tree[i].query(x);

        int m = (s + e) >> 1;
        return max({tree[i].query(x), query(2 * i, s, m, idx, x), query(2 * i + 1, m + 1, e, idx, x)});
    }

public:
    OfflineLiChaoTree() : q_idx(0) {}

    int add_line(ll a, ll b)
    {
        q.push_back({++q_idx, -1, a, b});
        return q.size() - 1;
    }

    void delete_line(int i)
    {
        get<1>(q[i]) = ++q_idx;
    }

    void query(ll x)
    {
        q2.push_back({++q_idx, x});
    }

    // return -INF if empty
    vector<ll> get_ans()
    {
        for (auto [l, r, a, b] : q)
            insert(1, 1, q_idx, l, (r == -1 ? q_idx : r), {a, b});

        for (auto [idx, x] : q2)
            ans.push_back(query(1, 1, q_idx, idx, x));

        return ans;
    }
};

ll ans[100005], D[100005];
int query[100005];
int V[100005], S[100005];
bool visit[100005];
vector<pii> adj[100005];
OfflineLiChaoTree T;
int cnt = 0;

void dfs(int s, ll dist)
{
    visit[s] = true;
    D[s] = dist;

    T.query(V[s]);
    query[cnt++] = s;
    int idx = T.add_line(D[s], -D[s] * V[s] - S[s]);

    for (auto [e, w] : adj[s])
    {
        if (!visit[e])
        {
            dfs(e, dist + w);
        }
    }
    T.delete_line(idx);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    for (int i = 2; i <= n; i++)
        cin >> S[i] >> V[i];

    dfs(1, 0);

    auto vt = T.get_ans();
    for (int i = 0; i < cnt; i++)
    {
        ans[query[i]] = vt[i];
    }
    for (int i = 2; i <= n; i++)
    {
        // cout << ans[i] << " " << (ll)D[i] * V[i] + S[i] << " -> ";
        cout << -ans[i] + (ll)D[i] * V[i] + S[i] << "\n";
    }
}