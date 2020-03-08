#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

class PersistentLiChaoTree
{
private:
    struct Line
    {
        int idx;
        ll a, b;
        Line(ll a, ll b, int idx = -1) : a(a), b(b), idx(idx) {}
        Line() {}
        ll f(ll x)
        {
            return a * x + b;
        }
    };

    struct Node
    {
        int l, r;
        ll xl, xr;
        Line line;
        Node(int l, int r, ll xl, ll xr, Line line) : l(l), r(r), xl(xl), xr(xr), line(line) {}
    };

    struct Info
    {
        int l, r;
        ll a, b;
    };

    vector<Node> tree;

    map<int, vector<pair<int, Info>>> change;
    ll s = -2e9, e = 2e9;
    int idx = 0;

public:
    PersistentLiChaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    void add_line(Line new_line, int i = 0)
    {
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;

        change[idx].push_back({i, {tree[i].l, tree[i].r, tree[i].line.a, tree[i].line.b}});

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
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm)
            return max(tree[i].line.f(x), query(x, tree[i].l));
        else
            return max(tree[i].line.f(x), query(x, tree[i].r));
    }

    void finish()
    {
        idx++;
    }

    void return_back()
    {
        for (auto &[i, info] : change[--idx])
        {
            tree[i].l = info.l;
            tree[i].r = info.r;
            tree[i].line.a = info.a;
            tree[i].line.b = info.b;
        }
        change[idx].clear();
    }
};

ll dp[100005];
int V[100005], S[100005];
bool visit[100005];
vector<pii> adj[100005];
PersistentLiChaoTree T;

void dfs(int s, ll dist)
{
    visit[s] = true;

    dp[s] = (s == 1 ? 0 : -T.query(V[s]));
    dp[s] += dist * V[s] + S[s];

    T.add_line({dist, -dp[s]});
    T.finish();
    for (auto [e, w] : adj[s])
    {
        if (!visit[e])
        {
            dfs(e, dist + w);
        }
    }
    T.return_back();
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

    for (int i = 2; i <= n; i++)
    {
        cout << dp[i] << " ";
    }
}