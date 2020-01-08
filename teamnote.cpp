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
void radix_sort(vector<pair<pii, int>> &vec, int num)
{
    int size = vec.size();
    vector<pair<pii, int>> temp;
    temp.resize(size);
    vector<int> cnt;
    cnt.resize(num + 1);
    for (int i = 0; i < size; i++)
        cnt[vec[i].first.second + 1]++;
    for (int i = 1; i < num + 1; i++)
        cnt[i] += cnt[i - 1];
    for (int i = size - 1; i >= 0; i--)
        temp[--cnt[vec[i].first.second + 1]] = vec[i];
    cnt.resize(num);
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < size; i++)
        cnt[temp[i].first.first]++;
    for (int i = 1; i < num; i++)
        cnt[i] += cnt[i - 1];
    for (int i = size - 1; i >= 0; i--)
        vec[--cnt[temp[i].first.first]] = temp[i];
}
vector<int> get_suffix_array(string s)
{
    int len = s.length();
    vector<pair<pii, int>> sa_node;
    vector<int> pos;
    pos.resize(len);
    for (int i = 0; i < len; i++)
    {
        pii rank(s[i] - 'a', i == len - 1 ? -1 : s[i + 1] - 'a');
        sa_node.push_back(make_pair(rank, i));
    }
    sort(sa_node.begin(), sa_node.end());
    for (int d = 2; d < len; d <<= 1)
    {
        int num_rank = 0, tmp = sa_node[0].first.first;
        sa_node[0].first.first = 0;
        pos[sa_node[0].second] = 0;
        for (int i = 1; i < len; i++)
        {
            pii pair_tmp(tmp, sa_node[i - 1].first.second);
            if (pair_tmp == sa_node[i].first)
                sa_node[i].first.first = num_rank;
            else
            {
                tmp = sa_node[i].first.first;
                sa_node[i].first.first = ++num_rank;
            }
            pos[sa_node[i].second] = i;
        }
        ++num_rank;
        for (int i = 0; i < len; i++)
        {
            int j = sa_node[i].second + d;
            if (j < len)
                sa_node[i].first.second = sa_node[pos[j]].first.first;
            else
                sa_node[i].first.second = -1;
        }
        radix_sort(sa_node, num_rank);
    }
    vector<int> sa;
    for (int i = 0; i < len; i++)
        sa.push_back(sa_node[i].second);
    return sa;
}
vector<int> get_lcp(string s, vector<int> sa)
{
    int len = sa.size();
    vector<int> rnk(len), lcp(len - 1);
    for (int i = 0; i < len; i++)
        rnk[sa[i]] = i;
    for (int i = 0, k = 0; i < len; i++)
    {
        if (rnk[i] == len - 1)
            continue;
        for (int j = sa[rnk[i] + 1]; i + k < len && j + k < len && s[i + k] == s[j + k]; k++)
            ;
        lcp[rnk[i]] = k;
        if (k > 0)
            k--;
    }
    return lcp;
}
class SegmentTree
{
private:
    vector<ll> tree, lazy;
    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += (e - s + 1) * lazy[i];
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
        lazy.resize(4 * (n + 1), 0);
    }
    void update_idx(int i, int s, int e, int idx, ll diff)
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
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    void update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] += diff;
            update_lazy(i, s, e);
        }
        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
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
        ll ret = 0;
        while (hld[u] != hld[v])
        {
            ret = ret + Tree.query(1, 1, n, num[hld[v]], num[v]);
            v = parent[hld[v]];
        }
        return ret + Tree.query(1, 1, n, num[u] + out, num[v]);
    }
    void _update_path(int u, int v, ll diff, bool out)
    {
        while (hld[u] != hld[v])
        {
            Tree.update_range(1, 1, n, num[hld[v]], num[v], diff);
            v = parent[hld[v]];
        }
        Tree.update_range(1, 1, n, num[u] + out, num[v], diff);
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
    bool flag, node;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;
    HeavyLightDecomposition(int n, bool node, int root = 1)
        : Tree(n), n(n), adj(n + 1), weight(n + 1, 0), parent(n + 1, 0), num_end(n + 1, 0),
          depth(n + 1, 0), num(n + 1, 0), idx(n + 1, 0), hld(n + 1, 0), cnt(0), node(node)
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
    void update_subtree(int i, ll diff)
    {
        init();
        Tree.update_range(1, 1, n, num[i], num_end[i], diff);
    }
    void update_path(int u, int v, ll diff)
    {
        init();
        int lca = LCA(u, v);
        _update_path(lca, u, diff, false);
        _update_path(lca, v, diff, node);
    }
    ll query_subtree(int i)
    {
        init();
        return Tree.query(1, 1, n, num[i], num_end[i]);
    }
    ll query_path(int u, int v)
    {
        init();
        int lca = LCA(u, v);
        return _query(lca, u, false) + _query(lca, v, node);
    }
};
class TwoSatisfiability
{
private:
    struct StronglyConnectedComponent
    {
        vector<vector<int>> adj, rev_adj, new_adj, scc_node;
        vector<int> st, temp, visit, scc;
        vector<pii> edge;
        int scc_cnt = 0, n;
        StronglyConnectedComponent(int n) : n(n)
        {
            scc_node.resize(n + 1);
            adj.resize(n + 1);
            rev_adj.resize(n + 1);
            new_adj.resize(n + 1);
            visit.resize(n + 1);
            scc.resize(n + 1);
        }
        void add_edge(int u, int v)
        {
            adj[u].push_back(v);
            rev_adj[v].push_back(u);
            edge.push_back({u, v});
        }
        void dfs(int s, bool flag)
        {
            visit[s] = true;
            for (auto e : (flag ? adj[s] : rev_adj[s]))
            {
                if (!visit[e])
                    dfs(e, flag);
            }
            (flag ? st : temp).push_back(s);
        }
        void make_scc()
        {
            for (int i = 1; i <= n; i++)
            {
                sort(adj[i].begin(), adj[i].end());
                sort(rev_adj[i].begin(), rev_adj[i].end());
            }
            for (int i = 1; i <= n; i++)
                if (!visit[i])
                    dfs(i, true);
            fill(visit.begin(), visit.end(), 0);
            while (!st.empty())
            {
                int s = st.back();
                st.pop_back();
                if (!visit[s])
                {
                    scc_cnt++;
                    dfs(s, false);
                    for (auto i : temp)
                    {
                        scc[i] = scc_cnt;
                        scc_node[scc_cnt].push_back(i);
                    }
                    temp.clear();
                }
            }
        }
        void topological_sort(int s)
        {
            visit[s] = true;
            for (auto e : new_adj[s])
                if (!visit[e])
                    topological_sort(e);
            st.push_back(s);
        }
        void make_dag()
        {
            for (auto [u, v] : edge)
                if (scc[u] != scc[v])
                    new_adj[scc[u]].push_back(scc[v]);
            fill(visit.begin(), visit.end(), 0);
            for (int i = 1; i <= n; i++)
                if (!visit[scc[i]])
                    topological_sort(scc[i]);
        }
    };

public:
    int n;
    vector<int> sat;
    StronglyConnectedComponent SCC;
    TwoSatisfiability(int n) : SCC(2 * n), n(n)
    {
        sat.resize(n + 1, -1);
    }
    void add_edge(int x1, int x2)
    {
        SCC.add_edge((x1 < 0 ? -x1 : x1 + n), (x2 < 0 ? -x2 + n : x2));
        SCC.add_edge((x2 < 0 ? -x2 : x2 + n), (x1 < 0 ? -x1 + n : x1));
    }
    bool satisfy()
    {
        SCC.make_scc();
        SCC.make_dag();
        for (int i = 1; i <= n; i++)
        {
            if (SCC.scc[i] == SCC.scc[i + n])
                return false;
        }
        auto &st = SCC.st;
        while (!st.empty())
        {
            int s = st.back();
            st.pop_back();
            for (auto e : SCC.scc_node[s])
            {
                bool flag = (e > n ? true : false);
                e = (e > n ? e - n : e);
                if (sat[e] == -1)
                    sat[e] = flag;
            }
        }
        return true;
    }
};
using cp = complex<long double>;
using func = vector<cp>;
class FastFourierTransform
{
private:
    const double PI = acos(-1);
    void FFT(func &f, cp w)
    {
        int n = f.size();
        if (n == 1)
            return;
        func even(n / 2), odd(n / 2);
        for (int i = 0; i < n; i++)
            (i & 1 ? odd : even)[i / 2] = f[i];
        FFT(even, w * w);
        FFT(odd, w * w);
        cp wp(1, 0);
        for (int i = 0; i < n / 2; i++)
        {
            f[i] = even[i] + wp * odd[i];
            f[i + n / 2] = even[i] - wp * odd[i];
            wp *= w;
        }
    }

public:
    func multiply(func f, func g)
    {
        int sz = f.size() + g.size() - 1;
        int n = 1;
        while (n < f.size() + 1 || n < g.size() + 1)
            n *= 2;
        n *= 2;
        func h(n);
        f.resize(n);
        g.resize(n);
        cp w(cos(2 * PI / n), sin(2 * PI / n));
        FFT(f, w);
        FFT(g, w);
        for (int i = 0; i < n; i++)
            h[i] = f[i] * g[i];
        FFT(h, cp(1, 0) / w);
        for (int i = 0; i < n; i++)
        {
            h[i] /= cp(n, 0);
            h[i] = cp(round(h[i].real()), round(h[i].imag()));
        }
        while (h.size() != sz)
            h.pop_back();
        return h;
    }
};
class FenwickTree
{
private:
    int n;
    vector<ll> tree;
    ll _query(int idx)
    {
        ll ret = 0;
        while (idx)
        {
            ret += tree[idx];
            idx -= (-idx & idx);
        }
        return ret;
    }

public:
    FenwickTree(int n) : n(n)
    {
        tree.resize(n + 10, 0);
    }
    void update(int idx, ll diff)
    {
        while (idx <= n)
        {
            tree[idx] += diff;
            idx += (-idx & idx);
        }
    }
    ll query(int l, int r)
    {
        return _query(r) - _query(l - 1);
    }
};
struct StronglyConnectedComponent
{
    vector<vector<int>> adj, rev_adj, new_adj, scc_node;
    vector<int> st, temp, visit, scc;
    vector<pii> edge;
    int scc_cnt = 0, n;
    StronglyConnectedComponent(int n) : n(n)
    {
        scc_node.resize(n + 1);
        adj.resize(n + 1);
        rev_adj.resize(n + 1);
        new_adj.resize(n + 1);
        visit.resize(n + 1);
        scc.resize(n + 1);
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        edge.push_back({u, v});
    }
    void dfs(int s, bool flag)
    {
        visit[s] = true;
        for (auto e : (flag ? adj[s] : rev_adj[s]))
        {
            if (!visit[e])
                dfs(e, flag);
        }
        (flag ? st : temp).push_back(s);
    }
    void make_scc()
    {
        for (int i = 1; i <= n; i++)
        {
            sort(adj[i].begin(), adj[i].end());
            sort(rev_adj[i].begin(), rev_adj[i].end());
        }
        for (int i = 1; i <= n; i++)
            if (!visit[i])
                dfs(i, true);
        fill(visit.begin(), visit.end(), 0);
        while (!st.empty())
        {
            int s = st.back();
            st.pop_back();
            if (!visit[s])
            {
                scc_cnt++;
                dfs(s, false);
                for (auto i : temp)
                {
                    scc[i] = scc_cnt;
                    scc_node[scc_cnt].push_back(i);
                }
                temp.clear();
            }
        }
    }
    void topological_sort(int s)
    {
        visit[s] = true;
        for (auto e : new_adj[s])
            if (!visit[e])
                topological_sort(e);
        st.push_back(s);
    }
    void make_dag()
    {
        for (auto [u, v] : edge)
            if (scc[u] != scc[v])
                new_adj[scc[u]].push_back(scc[v]);
        fill(visit.begin(), visit.end(), 0);
        for (int i = 1; i <= n; i++)
            if (!visit[scc[i]])
                topological_sort(scc[i]);
    }
};
ll power(int a, int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return a;
    ll b = power(a, n / 2);
    return (n % 2 == 1 ? (((b * b) % MOD) * a) % MOD : ((b * b) % MOD));
}
using Matrix = vector<vector<ll>>;
Matrix matmake(int r, int c)
{
    return Matrix(r, vector<ll>(c, 0));
}
Matrix matmul(Matrix A, Matrix B)
{
    int a = A.size();
    int b = A[0].size();
    int c = B[0].size();
    Matrix ret;
    ret.resize(a, vector<ll>(c, 0));
    for (int i = 0; i < a; i++)
        for (int j = 0; j < c; j++)
            for (int k = 0; k < b; k++)
            {
                ret[i][j] += A[i][k] * B[k][j];
                ret[i][j] %= MOD;
            }
    return ret;
}
Matrix matpow(Matrix A, int m)
{
    if (m == 1)
        return A;
    Matrix B = matpow(A, m / 2);
    if (m % 2 == 0)
        return matmul(B, B);
    else
        return matmul(A, matmul(B, B));
}
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
using ld = long double;
class ConvexHullTrick
{
private:
    struct Line
    {
        ll s, i;
        Line(ll _s, ll _i) : s(_s), i(_i) {}
    };
    vector<Line> st;
    ld cross_point(Line a, Line b)
    {
        if (a.s == b.s)
            return (a.i > b.i ? INF : -INF);
        return (ld)(a.i - b.i) / (b.s - a.s);
    }
    void push_line(Line ins)
    {
        while (st.size() >= 2 && cross_point(st[st.size() - 2], st.back()) > cross_point(st.back(), ins))
            st.pop_back();
        st.push_back(ins);
    }

public:
    void add_line(ll a, ll b)
    {
        push_line(Line(a, b));
    }
    ll get_max_v1(ll x)
    {
        static ll ptr = 0;
        ptr = (ptr >= st.size() ? st.size() - 1 : ptr);
        while (ptr + 1 != st.size() && cross_point(st[ptr], st[ptr + 1]) < x)
            ptr++;
        return x * st[ptr].s + st[ptr].i;
    }
    ll get_max_v2(ll x)
    {
        int s = 0, e = st.size() - 1;
        while (s <= e)
        {
            int m = (s + e) / 2;
            if (cross_point(st[m], st[m - 1]) > x)
                e = m - 1;
            else
                s = m + 1;
        }
        return x * st[s].s + st[s].i;
    }
};
using pll = pair<ll, ll>;
class CCW
{
private:
    int ccw(pll a, pll b, pll c)
    {
        int op = a.first * b.second + b.first * c.second + c.first * a.second;
        op -= (a.second * b.first + b.second * c.first + c.second * a.first);
        if (op > 0)
            return 1;
        else if (op == 0)
            return 0;
        else
            return -1;
    }

public:
    bool in_convex_hull(pll a, vector<pll> &vt)
    {
        for (int i = 1; i <= vt.size(); i++)
            if (ccw(vt[i % vt.size()], a, vt[(i - 1) % vt.size()]) < 0)
                return false;
        return true;
    }
    bool is_intersect(pair<pll, pll> x, pair<pll, pll> y)
    {
        auto [a, b] = x;
        auto [c, d] = y;
        int ab = ccw(a, b, c) * ccw(a, b, d);
        int cd = ccw(c, d, a) * ccw(c, d, b);
        if (ab == 0 && cd == 0)
        {
            if (a > b)
                swap(a, b);
            if (c > d)
                swap(c, d);
            return c <= b && a <= d;
        }
        return ab <= 0 && cd <= 0;
    }
};
using ld = long double;
using pld = pair<ld, ll>;
using pll = pair<ll, ll>;
class ConvexHull
{
private:
    const ll INF = 98765432123456789;
    pll first = {INF, INF};
    vector<pll> points;
    pld converter(const pll &dot)
    {
        auto [x1, y1] = dot;
        auto [x2, y2] = first;
        auto dx = x2 - x1, dy = y2 - y1;
        if (x1 == x2)
            return {INF, dx * dx + dy * dy};
        else
            return {(ld)dy / dx, dx * dx + dy * dy};
    }
    ll outer_product(const pll &a, const pll &b, const pll &c)
    {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        auto [x3, y3] = c;
        return (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    }

public:
    void add_point(int x, int y)
    {
        points.push_back({x, y});
        first = min(first, points.back());
    }
    vector<pll> convex_hull()
    {
        vector<pll> vt;
        sort(points.begin(), points.end(), [&](const pll &a, const pll &b) { return converter(a) < converter(b); });
        vt.push_back(first);
        for (auto &p : points)
        {
            if (p == first)
                continue;
            while (vt.size() >= 2)
            {
                int k = vt.size() - 1;
                auto &a = vt[k], &b = vt[k - 1];
                if (outer_product(b, a, p) >= 0)
                {
                    if (outer_product(b, a, p) == 0)
                        vt.pop_back();
                    break;
                }
                else
                    vt.pop_back();
            }
            vt.push_back(p);
        }
        return vt;
    }
};
class ExtendedGCD
{
private:
    vector<int> x, y, r, q;
    int gcd(int a, int b)
    {
        return (a % b == 0 ? b : gcd(b, a % b));
    }

public:
    // solve ax + by = c
    pii solve_equation(int a, int b, int c)
    {
        if (c % gcd(a, b) != 0)
            return {INF, INF};
        x = {1, 0};
        y = {0, 1};
        r = {a, b};
        while (1)
        {
            int r2 = r[r.size() - 2];
            int r1 = r[r.size() - 1];
            q.push_back(r2 / r1);
            r.push_back(r2 % r1);
            if (r[r.size() - 1] == 0)
                break;
            int x1 = x[x.size() - 1];
            int x2 = x[x.size() - 2];
            int y1 = y[y.size() - 1];
            int y2 = y[y.size() - 2];
            int q1 = q[q.size() - 1];
            x.push_back(x2 - x1 * q1);
            y.push_back(y2 - y1 * q1);
        }
        int mul = c / gcd(a, b);
        pii ret = {x[x.size() - 1] * mul, y[y.size() - 1] * mul};
        x.clear(), y.clear(), r.clear(), q.clear();
        return ret;
    }
};
class Trie
{
private:
    Trie *next[26];

public:
    bool finish;
    int cnt;
    Trie()
    {
        finish = false;
        cnt = 0;
        memset(next, 0, sizeof(next));
    }
    void insert(const char *key)
    {
        if (*key == '\0')
            finish = true;
        else
        {
            int cur = *key - 'a';
            if (!next[cur])
                next[cur] = new Trie();
            next[cur]->insert(key + 1);
        }
    }
    Trie *find(const char *key)
    {
        if (*key == '\0')
            return this;
        int cur = *key - 'a';
        if (!next[cur])
            return NULL;
        return next[cur]->find(key + 1);
    }
};
class DynamicSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll value;
        Node() : l(0), r(0), value(0) {}
    };
    vector<Node> tree;
    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
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
    ll _query(int i, ll s, ll e, ll l, ll r)
    {
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
        return _query(1, s, e, l, r);
    }
    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }
    ll kth(ll sum)
    {
        return _kth(1, s, e, sum);
    }
};
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
class Tree
{
private:
    vector<vector<pii>> adj;
    vector<vector<int>> p;
    vector<int> depth, dis;
    bool flag = true;
    int root = 1, n;
    void dfs_numbering(int s, int dist, int d)
    {
        depth[s] = d;
        dis[s] = dist;
        for (auto [e, cost] : adj[s])
        {
            if (!depth[e])
            {
                p[e][0] = s;
                dfs_numbering(e, dist + cost, d + 1);
            }
        }
    }
    void init()
    {
        dfs_numbering(1, 0, 1);
        for (int i = 1; i <= 20; i++)
            for (int me = 1; me <= n; me++)
                p[me][i] = p[p[me][i - 1]][i - 1];
    }

public:
    Tree(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        p.resize(n + 1);
        for (int i = 0; i <= n; i++)
            p[i].resize(22, 0);
        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
    }
    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    int LCA(int a, int b)
    {
        if (flag)
        {
            flag = false;
            init();
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int da = depth[a], db = depth[b];
        while (db - da)
        {
            int x = log2(db - da);
            int delta = 1 << x;
            db -= delta;
            b = p[b][x];
        }
        if (a == b)
            return a;
        for (int i = 20; i >= 0; i--)
            if (p[a][i] != p[b][i])
                a = p[a][i], b = p[b][i];
        return p[a][0];
    }
    ll dist(int a, int b)
    {
        int lca = LCA(a, b);
        return (ll)dis[a] + dis[b] - 2 * dis[lca];
    }
};
class SegmentTree
{
private:
    vector<ll> tree, lazy;
    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += (e - s + 1) * lazy[i];
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
        lazy.resize(4 * (n + 1), 0);
    }
    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    void update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] += diff;
            update_lazy(i, s, e);
        }
        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
    int kth(int i, int s, int e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        int m = (s + e) / 2;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};
class MinCostMaxFlow
{
private:
    struct Edge
    {
        int to, flow, cap, cost, rev;
        Edge(int to, int cap, int cost)
            : to(to), cap(cap), cost(cost), flow(0) {}
    };
    vector<vector<Edge>> adj;
    vector<pii> prev;
    vector<int> dis;
    vector<bool> in_queue;

public:
    int source, sink, fake_source;
    MinCostMaxFlow(int n)
    {
        source = 0;
        sink = n + 1;
        adj.resize(sink + 1);
        prev.resize(sink + 1, pii(-1, -1));
        dis.resize(sink + 1, INF);
        in_queue.resize(sink + 1, false);
    }
    void add_edge(int from, int to, int cap, int cost)
    {
        adj[from].push_back(Edge(to, cap, cost));
        adj[to].push_back(Edge(from, 0, -cost));
        adj[from].back().rev = adj[to].size() - 1;
        adj[to].back().rev = adj[from].size() - 1;
    }
    pii mcmf()
    {
        int cost = 0, flow = 0;
        while (1)
        {
            fill(prev.begin(), prev.end(), pii(-1, -1));
            fill(dis.begin(), dis.end(), INF);
            queue<int> q;
            q.push(source);
            in_queue[source] = true;
            dis[source] = 0;
            while (!q.empty())
            {
                int s = q.front();
                q.pop();
                in_queue[s] = false;
                for (int i = 0; i < adj[s].size(); i++)
                {
                    auto &e = adj[s][i];
                    if (dis[e.to] > dis[s] + e.cost && e.cap - e.flow > 0)
                    {
                        dis[e.to] = dis[s] + e.cost;
                        prev[e.to] = {s, i};
                        if (!in_queue[e.to])
                        {
                            in_queue[e.to] = true;
                            q.push(e.to);
                        }
                    }
                }
            }
            if (dis[sink] == INF)
                break;
            int f = INF;
            for (int i = sink; i != source; i = prev[i].first)
            {
                auto &e = adj[prev[i].first][prev[i].second];
                f = min(f, e.cap - e.flow);
            }
            for (int i = sink; i != source; i = prev[i].first)
            {
                auto &e = adj[prev[i].first][prev[i].second];
                e.flow += f;
                adj[e.to][e.rev].flow -= f;
                cost += e.cost * f;
            }
            flow += f;
        }
        return pii(cost, flow);
    }
};
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
};