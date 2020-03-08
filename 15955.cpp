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
const int MAX = -1;

class MaxSegmentTree
{
private:
    vector<ll> tree;

public:
    MaxSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
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

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

class HeavyLightDecomposition
{
private:
    void dfs1(int s)
    {
        weight[s] = 1;
        for (auto e : adj[s])
        {
            if (!weight[e])
            {
                parent[e] = s;
                depth[e] = depth[s] + 1;
                dfs1(e);
                weight[s] += weight[e];
            }
        }
    }

    void dfs2(int s)
    {
        int E = -1;
        num[s] = ++cnt;
        idx[cnt] = s;

        for (auto e : adj[s])
            if (parent[e] == s && (E == -1 || weight[E] < weight[e]))
                E = e;

        if (E != -1)
            hld[E] = hld[s], dfs2(E);

        for (auto e : adj[s])
            if (parent[e] == s && e != E)
                hld[e] = e, dfs2(e);

        num_end[s] = cnt;
    }

    ll _query(int u, int v, bool out)
    {
        ll ret = -INF;
        while (hld[u] != hld[v])
        {
            ret = max(ret, Tree.query(1, 1, n, num[hld[v]], num[v]));
            v = parent[hld[v]];
        }
        return max(ret, Tree.query(1, 1, n, num[u] + out, num[v]));
    }

    void init()
    {
        if (flag)
            return;

        for (int i = 1; i <= n; i++)
            if (!weight[i])
                hld[i] = parent[i] = i, dfs1(i);

        for (int i = 1; i <= n; i++)
            if (!num[i])
                dfs2(i);

        flag = true;
    }

public:
    int n, cnt, root;
    bool flag, edge;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    MaxSegmentTree Tree;

    HeavyLightDecomposition(int n, bool edge, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), edge(edge)
    {
        flag = false;
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int LCA(int u, int v)
    {
        init();
        while (hld[u] != hld[v])
        {
            if (depth[hld[u]] > depth[hld[v]])
                u = parent[hld[u]];
            else
                v = parent[hld[v]];
        }
        return (depth[u] < depth[v] ? u : v);
    }

    void update_node(int i, ll diff)
    {
        init();
        Tree.update_idx(1, 1, n, num[i], diff);
    }

    void update_edge(int u, int v, ll diff)
    {
        init();
        update_node((parent[u] == v ? u : v), diff);
    }

    ll query_path(int u, int v)
    {
        init();
        int lca = LCA(u, v);
        return max(_query(lca, u, true), _query(lca, v, edge));
    }
};

int parent[500005];
int find(int me)
{
    if (parent[me] < 0)
        return me;
    else
        return parent[me] = find(parent[me]);
}

void uni(int a, int b)
{
    a = find(a), b = find(b);
    if (a != b)
    {
        parent[a] += parent[b];
        parent[b] = a;
    }
}
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n, m;
    cin >> n >> m;
    HeavyLightDecomposition HLD(n, true);

    using tt = tuple<ll, ll, ll>;
    vector<tuple<ll, ll, ll>> point;

    for (int i = 0; i < n; i++)
    {
        ll x, y;
        cin >> x >> y;
        point.push_back({x, y, i + 1});
    }

    vector<tuple<ll, ll, ll>> edge;

    sort(point.begin(), point.end());
    for (int i = 0; i < n - 1; i++)
    {
        ll dx = abs(get<0>(point[i]) - get<0>(point[i + 1]));
        ll dy = abs(get<1>(point[i]) - get<1>(point[i + 1]));
        edge.push_back({min(dx, dy), get<2>(point[i]), get<2>(point[i + 1])});
    }

    sort(point.begin(), point.end(), [](tt &a, tt &b) { return get<1>(a) < get<1>(b); });
    for (int i = 0; i < n - 1; i++)
    {
        ll dx = abs(get<0>(point[i]) - get<0>(point[i + 1]));
        ll dy = abs(get<1>(point[i]) - get<1>(point[i + 1]));
        edge.push_back({min(dx, dy), get<2>(point[i]), get<2>(point[i + 1])});
    }

    sort(edge.begin(), edge.end());

    vector<tuple<ll, ll, ll>> upd;
    for (auto [w, u, v] : edge)
    {
        // cout << w << " " << u << " " << v << "\n";
        if (find(u) != find(v))
        {
            uni(u, v);
            HLD.add_edge(u, v);
            upd.push_back({w, u, v});
        }
    }

    // cout << upd.size() << "\n";
    for (auto [w, u, v] : upd)
    {
        HLD.update_edge(u, v, w);
    }

    while (m--)
    {
        ll x, y, z;
        cin >> x >> y >> z;
        // cout << HLD.query_path(x, y) << "\n";
        if (HLD.query_path(x, y) > z)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
}