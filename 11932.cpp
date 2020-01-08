#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

class PersistentSegmentTree
{
private:
    struct Node
    {
        Node() : v(0), left(0), right(0) {}
        int v, left, right;
    };

    vector<Node> tree;
    vector<int> tree_idx;
    vector<int> y;
    int xs, xe, ys, ye;
    bool flag = true;

    int make_tree(int cur, int ys, int ye, int y, int v)
    {
        if (!(ys <= y && y <= ye))
            return cur;

        int ret = tree.size();
        tree.push_back(Node());

        if (ys == ye)
        {
            tree[ret].v = tree[cur].v + v;
            return ret;
        }

        int ym = (ys + ye) >> 1;
        tree[ret].left = make_tree(tree[cur].left, ys, ym, y, v);
        tree[ret].right = make_tree(tree[cur].right, ym + 1, ye, y, v);
        tree[ret].v = tree[tree[ret].left].v + tree[tree[ret].right].v;
        return ret;
    }

    int init_first_tree(int ys, int ye)
    {
        int ret = tree.size();
        tree.push_back(Node());

        if (ys == ye)
            return ret;

        int ym = (ys + ye) >> 1;

        tree[ret].left = init_first_tree(ys, ym);
        tree[ret].right = init_first_tree(ym + 1, ye);
        tree[ret].v = tree[tree[ret].left].v + tree[tree[ret].right].v;
        return ret;
    }

    int _query(int cur, int ys, int ye, int yl, int yr)
    {
        if (ys > yr || ye < yl || !cur)
            return 0;
        else if ((yl <= ys && ye <= yr))
            return tree[cur].v;
        int ym = (ys + ye) >> 1;
        return _query(tree[cur].left, ys, ym, yl, yr) + _query(tree[cur].right, ym + 1, ye, yl, yr);
    }

public:
    // make [0, n] x [0, n] persistent segment tree
    PersistentSegmentTree(int n) : xs(0), xe(n), ys(0), ye(n), tree_idx(n + 1)
    {
        tree.push_back(Node());
        y.resize(n + 1);
    }

    void add_point(int x, int y)
    {
        this->y[x] = y;
    }

    int query(int u, int v, int lca, int k)
    {
        int w = y[lca] <= k;
        int x = _query(tree_idx[u], ys, ye, 0, k);
        int y = _query(tree_idx[v], ys, ye, 0, k);
        int z = _query(tree_idx[lca], ys, ye, 0, k);

        return (w + x + y) - 2 * z;
    }

    void init(vector<pii> &edge)
    {
        tree_idx[1] = init_first_tree(ys, ye);
        tree_idx[1] = make_tree(tree_idx[1], ys, ye, y[1], 1);

        for (auto [p, c] : edge)
            tree_idx[c] = make_tree(tree_idx[p], ys, ye, y[c], 1);
    }
};

class Tree
{
private:
    vector<vector<pii>> adj;
    vector<vector<int>> p;
    vector<int> depth, dis;
    bool flag = true;
    int n, k = 20;

    void dfs(int s, ll dist, int d)
    {
        depth[s] = d;
        dis[s] = dist;

        for (auto [e, cost] : adj[s])
        {
            if (!depth[e])
            {
                p[e][0] = s;
                dfs(e, dist + cost, d + 1);
            }
        }
    }

    void init()
    {
        if (!flag)
            return;

        flag = false;
        dfs(1, 0, 1);
        for (int i = 1; i <= k; i++)
            for (int me = 1; me <= n; me++)
                p[me][i] = p[p[me][i - 1]][i - 1];
    }

public:
    Tree(int n) : n(n)
    {
        adj.resize(n + 1);
        p.resize(n + 1);

        for (int i = 0; i <= n; i++)
            p[i].resize(k + 1, 0);

        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    int LCA(int u, int v)
    {
        init();

        for (int i = k; i >= 0; i--)
            if (depth[p[u][i]] >= depth[v])
                u = p[u][i];

        for (int i = k; i >= 0; i--)
            if (depth[p[v][i]] >= depth[u])
                v = p[v][i];

        for (int i = k; i >= 0; i--)
            if (p[u][i] != p[v][i])
                u = p[u][i], v = p[v][i];

        return (u == v ? u : p[u][0]);
    }

    int raise_node(int u, int d)
    {
        init();
        for (int i = k, j; i >= 0 && (j = 1 << i); i--)
            if (j <= d)
                u = p[u][i], d -= j;
        return u;
    }

    ll dist(int a, int b)
    {
        init();
        int lca = LCA(a, b);
        return (ll)dis[a] + dis[b] - 2 * dis[lca];
    }

    vector<pii> get_edge_list()
    {
        init();
        vector<pii> ret;
        queue<int> q;
        q.push(1);
        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            for (auto [e, _] : adj[s])
            {
                if (p[e][0] == s)
                {
                    q.push(e);
                    ret.push_back({s, e});
                }
            }
        }
        return ret;
    }
};

char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}

int readInt()
{
    int ret = 0, flg = 1;
    char now = read();

    while (isspace(now))
        now = read();
    if (now == '-')
        flg = -1, now = read();
    while (now >= 48 && now <= 57)
    {
        ret = ret * 10 + now - 48;
        now = read();
    }
    return ret * flg;
}

vector<int> weight;
vector<int> cp;
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n = readInt(), q = readInt();

    Tree tree(n);

    weight.resize(n);

    for (int i = 0; i < n; i++)
    {
        weight[i] = readInt();
        cp.push_back(weight[i]);
    }

    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());

    PersistentSegmentTree pst(n);
    for (auto i = 0; i < n; i++)
        pst.add_point(i + 1, lower_bound(cp.begin(), cp.end(), weight[i]) - cp.begin());

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        u = readInt(), v = readInt();
        tree.add_edge(u, v);
    }

    auto edge = tree.get_edge_list();
    pst.init(edge);

    while (q--)
    {
        int u, v, k;
        u = readInt(), v = readInt(), k = readInt();

        int lca = tree.LCA(u, v);

        int s = 0, e = cp.size();
        while (s <= e)
        {
            int m = (s + e) >> 1;
            int x = pst.query(u, v, lca, m);

            if (x >= k)
                e = m - 1;
            else
                s = m + 1;
        }

        cout << cp[s] << "\n";
    }
}