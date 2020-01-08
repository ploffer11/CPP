#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int cnt[30][30];
int n, m;

class DynamicSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll value, lazy;
        Node() : l(0), r(0), value(0), lazy(0) {}
    };
    vector<Node> tree;

    void update_lazy(int i, ll s, ll e)
    {
        if (tree[i].lazy)
        {
            tree[i].value += (e - s + 1) * tree[i].lazy;
            if (s != e)
            {
                if (tree[i].l == 0)
                {
                    tree[i].l = tree.size();
                    tree.push_back(Node());
                }

                if (tree[i].r == 0)
                {
                    tree[i].r = tree.size();
                    tree.push_back(Node());
                }

                tree[tree[i].l].lazy += tree[i].lazy;
                tree[tree[i].r].lazy += tree[i].lazy;
            }
            tree[i].lazy = 0;
        }
    }

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        update_lazy(i, s, e);
        if (s == e)
        {
            tree[i].value += diff;
            return;
        }

        ll m = (s + e) / 2;
        if (idx <= m)
        {
            if (tree[i].l == 0)
            {
                tree[i].l = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].l, s, m, idx, diff);
        }
        else
        {
            if (tree[i].r == 0)
            {
                tree[i].r = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].r, m + 1, e, idx, diff);
        }
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    void _update_range(int i, ll s, ll e, ll l, ll r, ll diff)
    {
        update_lazy(i, s, e);
        if (e < l || s > r)
            return;

        if (l <= s && e <= r)
        {
            tree[i].lazy += diff;
            update_lazy(i, s, e);
            return;
        }

        ll m = (s + e) / 2;

        if (tree[i].l == 0)
        {
            tree[i].l = tree.size();
            tree.push_back(Node());
        }

        if (tree[i].r == 0)
        {
            tree[i].r = tree.size();
            tree.push_back(Node());
        }

        _update_range(tree[i].l, s, m, l, r, diff);
        _update_range(tree[i].r, m + 1, e, l, r, diff);
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        update_lazy(i, s, e);
        if (i == 0 || e < l || s > r)
            return 0;
        else if (l <= s && e <= r)
            return tree[i].value;
        else
        {
            ll m = (s + e) / 2;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

    ll _kth(int i, ll s, ll e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        ll m = (s + e) / 2;
        if (tree[tree[i].l].value < sum)
            return _kth(tree[i].r, m + 1, e, sum - tree[tree[i].l].value);
        else
            return _kth(tree[i].l, s, m, sum);
    }

public:
    ll s, e;
    DynamicSegmentTree(int cap)
    {
        tree.reserve(cap);
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 0;
        this->e = (ll)1e18 + 5;
    }

    ll query(ll l, ll r)
    {
        return rand() % m;
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }

    void update_range(ll l, ll r, ll diff)
    {
        _update_range(1, s, e, l, r, diff);
    }

    ll kth(ll sum)
    {
        return _kth(1, s, e, sum);
    }
};
#define fastio srand(3)
class Dinic
{
private:
    struct Edge
    {
        int to, rev, cap, flow;
        Edge(int _to, int _cap) : to(_to), cap(_cap), flow(0) {}
    };

    vector<vector<Edge>> adj;
    vector<int> depth, work;

    void bfs()
    {
        fill(depth.begin(), depth.end(), -1);

        queue<int> q;
        q.push(source);
        depth[source] = 0;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();

            for (auto &e : adj[s])
            {
                if (e.cap - e.flow > 0 && depth[e.to] == -1)
                {
                    depth[e.to] = depth[s] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int s, int flow)
    {
        if (s == sink)
            return flow;

        for (int i = work[s]; i < adj[s].size(); i++, work[s]++)
        {
            auto &e = adj[s][i];

            if (depth[e.to] == depth[s] + 1 && e.cap - e.flow > 0)
            {
                int f = dfs(e.to, min(flow, e.cap - e.flow));

                if (f < 0)
                    continue;

                e.flow += f;
                adj[e.to][e.rev].flow -= f;

                return f;
            }
        }

        return -1;
    }

public:
    int source, sink;

    Dinic(int n)
    {
        source = 0;
        sink = n + 1;

        adj.resize(sink + 1);
        depth.resize(sink + 1);
        work.resize(sink + 1);
    }

    void add_edge(int u, int v, int cap)
    {
        adj[u].push_back(Edge(v, cap));
        adj[v].push_back(Edge(u, 0));
        adj[u].back().rev = adj[v].size() - 1;
        adj[v].back().rev = adj[u].size() - 1;
    }

    int max_flow()
    {
        int flow = 0;
        while (1)
        {
            bfs();
            if (depth[sink] == -1)
                break;

            fill(work.begin(), work.end(), 0);
            while (1)
            {
                int f = dfs(source, 987654321);
                if (f < 0)
                    break;
                flow += f;
            }
        }

        return flow;
    }

    ll func(vector<int> &state, int i, int j, ll flow3, double &k)
    {
        swap(state[i], state[j]);
        ll flow2 = flow(state);

        if (exp((flow3 - flow2) / k) > (double)(rand() % 100) / 100)
            flow3 = flow2;
        else
            swap(state[i], state[j]);
        k *= 0.9999;
        return flow3;
    }

    ll flow(vector<int> &state)
    {
        ll ret = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                ret += cnt[min(state[i], state[j])][max(state[i], state[j])] * (j - i);
            }
        }
        return ret;
    }
};
int q = 1000000;
class PersistentSegmentTree
{
private:
    struct Node
    {
        Node() : v(0), left(0), right(0) {}
        int v;
        Node *left, *right;
    };
    vector<Node *> tree;
    vector<vector<int>> y;
    int xs, xe, ys, ye;
    bool flag = true;

    Node *make_tree(Node *cur, int ys, int ye, int y, int v)
    {
        if (!(ys <= y && y <= ye))
            return cur;
        Node *ret = new Node();
        if (ys == ye)
        {
            ret->v = cur->v + v;
            return ret;
        }
        int ym = (ys + ye) >> 1;
        ret->left = make_tree(cur->left, ys, ym, y, v);
        ret->right = make_tree(cur->right, ym + 1, ye, y, v);
        ret->v = (ret->left ? ret->left->v : 0) + (ret->right ? ret->right->v : 0);
        return ret;
    }

    Node *init_first_tree(int ys, int ye)
    {
        Node *ret = new Node();
        if (ys == ye)
        {
            ret->v = 0;
            return ret;
        }
        int ym = (ys + ye) >> 1;
        ret->left = init_first_tree(ys, ym);
        ret->right = init_first_tree(ym + 1, ye);
        ret->v = ret->left->v + ret->right->v;
        return ret;
    }

    int _query(Node *cur, int ys, int ye, int yl, int yr)
    {
        if (ys > yr || ye < yl || !cur)
            return 0;
        else if ((yl <= ys && ye <= yr))
            return cur->v;
        int ym = (ys + ye) >> 1;
        return _query(cur->left, ys, ym, yl, yr) + _query(cur->right, ym + 1, ye, yl, yr);
    }

    void init()
    {
        tree[xs] = init_first_tree(ys, ye);

        for (auto i : y[xs])
            tree[xs] = make_tree(tree[xs], ys, ye, i, 1);

        for (int i = 1; i <= xe; i++)
        {
            if (!y[i].empty())
            {
                tree[i] = make_tree(tree[i - 1], ys, ye, y[i][0], 1);
                for (int j = 1; j < y[i].size(); j++)
                    tree[i] = make_tree(tree[i], ys, ye, y[i][j], 1);
            }
            else
                tree[i] = tree[i - 1];
        }
    }

    int _kth(Node *tree1, Node *tree2, int ys, int ye, int k)
    {
        int ym = (ys + ye) >> 1;

        if (ys == ye)
            return ys;

        if (tree2->left->v - tree1->left->v >= k)
            return _kth(tree1->left, tree2->left, ys, ym, k);
        else
            return _kth(tree1->right, tree2->right, ym + 1, ye, k - (tree2->left->v - tree1->left->v));
    }

public:
    // make [0, n] x [0, n] segment tree
    PersistentSegmentTree(int n) : xs(0), xe(n), ys(0), ye(n)
    {
        tree.resize(n + 1);
        y.resize(n + 1);
    }

    void add_point(int x, int y)
    {
        this->y[x].push_back(y);
    }

    // query [xl, xr] x [yl, yr]
    int query(int xl, int xr, int yl, int yr)
    {
        if (flag)
        {
            init();
            flag = false;
        }

        return _query(tree[xr], ys, ye, yl, yr) - _query(tree[xl - 1], ys, ye, yl, yr);
    }

    // find min(y) that satisfies query [xl, xr] x [0, y] >= k
    int kth(int xl, int xr, int k)
    {
        if (flag)
        {
            init();
            flag = false;
        }

        return _kth(tree[xl - 1], tree[xr], ys, ye, k);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    fastio;
    Dinic dinic(1005);
    DynamicSegmentTree Tree(1005);
    string s;
    cin >> n >> m >> s;

    ll ans = INF;

    for (int i = 0; i < n - 1; i++)
        cnt[min(s[i], s[i + 1]) - 'a'][max(s[i], s[i + 1]) - 'a']++;

    vector<int> state;
    for (int i = 0; i < m; i++)
        state.push_back(i);

    ll flow = dinic.flow(state);
    double k = 10;
    while (q--)
    {
        ans = min(ans, flow);
        int i = Tree.query(n, m), j = Tree.query(n, m);

        if (i == j)
            continue;

        flow = dinic.func(state, i, j, flow, k);
    }
    cout << ans;
}