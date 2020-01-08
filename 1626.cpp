#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const ll INF = 123987654321;
const long long MOD = (long long)1 << 32;

pii f(pii a, pii b)
{
    auto [_1, _2] = a;
    auto [_3, _4] = b;
    vector<int> temp = {_1, _2, _3, _4};

    sort(temp.begin(), temp.end());
    temp.resize(unique(temp.begin(), temp.end()) - temp.begin());

    if (temp.size() == 1)
        return {temp.back(), -INF};
    else
        return {temp.back(), temp[temp.size() - 2]};
}

class SegmentTree
{
private:
    vector<pii> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), pii(-INF, -INF));
    }

    void update_idx(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = {diff, -INF};
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = f(tree[2 * i], tree[2 * i + 1]);
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
            return f(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
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

    pii _query(int u, int v, bool out)
    {
        pii ret = {-INF, -INF};
        while (hld[u] != hld[v])
        {
            ret = f(ret, Tree.query(1, 1, n, num[hld[v]], num[v]));
            v = parent[hld[v]];
        }
        return f(ret, Tree.query(1, 1, n, num[u] + out, num[v]));
    }

    void init()
    {
        if (!flag)
        {
            dfs1(root);
            dfs2(root);
        }
        flag = true;
    }

public:
    int n, cnt, root;
    bool flag;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;

    HeavyLightDecomposition(int n, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), root(root)
    {
        hld[root] = parent[root] = root;
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

    pii query_path(int u, int v)
    {
        init();
        int lca = LCA(u, v);
        return f(_query(lca, u, true), _query(lca, v, true));
    }
};

int parent[50005];
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
vector<tuple<int, int, int>> edge, mst, query;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int v, e;
    cin >> v >> e;
    HeavyLightDecomposition HLD(v);

    for (int i = 1; i <= e; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        edge.push_back({c, u, v});
    }

    sort(edge.begin(), edge.end());

    int cnt = 0;
    ll m = 0;
    for (auto [c, u, v] : edge)
    {
        if (find(u) == find(v))
            query.push_back({c, u, v});
        else
        {
            cnt++;
            m += c;
            uni(u, v);
            mst.push_back({c, u, v});
            HLD.add_edge(u, v);
        }
    }

    if (cnt != v - 1)
    {
        cout << "-1";
        return 0;
    }

    for (auto [c, u, v] : mst)
    {
        HLD.update_edge(u, v, c);
    }

    ll ans2 = (ll)INF * 100;
    for (auto [c, u, v] : query)
    {
        auto [x, y] = HLD.query_path(u, v);

        //cout << c << " " << x << " " << y << endl;
        if (x != c)
        {
            ans2 = min(ans2, m + c - x);
            continue;
        }

        if (y != -INF)
            ans2 = min(ans2, m + c - y);
    }

    cout << (ans2 == (ll)INF * 100 ? -1 : ans2);
}