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

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
}


class SPFA
{
private:
    int n;
    vector<bool> inq;
    vector<int> cycle, via;
    vector<ll> dis;
    vector<vector<pair<int, ll>>> adj;

public:
    SPFA(int n) : dis(n + 1), inq(n + 1), adj(n + 1), cycle(n + 1), via(n + 1), n(n) {}

    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
        fill(cycle.begin(), cycle.end(), 0);

        queue<int> q;
        dis[s] = 0;
        q.push(s);
        inq[s] = true;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inq[s] = false;
            cycle[s]++;

            if (cycle[s] == n)
                continue;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    via[e] = s;
                    if (!inq[e])
                    {
                        q.push(e);
                        inq[e] = true;
                    }
                }
            }
        }
        return dis[e];
    }
};

class Dijkstra
{
private:
    vector<vector<pair<int, ll>>> adj;
    vector<ll> dis;
    vector<int> via;
    vector<bool> finish;

public:
    Dijkstra(int n) : dis(n + 1), finish(n + 1), adj(n + 1), via(n + 1) {}
    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
        fill(finish.begin(), finish.end(), false);

        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0, s});
        dis[s] = 0;

        while (!pq.empty())
        {
            auto [cur, s] = pq.top();
            pq.pop();

            if (finish[s])
                continue;
            finish[s] = true;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    via[e] = s;
                    dis[e] = dis[s] + w;
                    pq.push({dis[e], e});
                }
            }
        }
        return dis[e];
    }
};

class DynamicMaxSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll v;
        Node() : l(0), r(0), v(-0x3f3f3f3f3f3f3f3f) {}
    };
    vector<Node> tree;

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        if (s == e)
        {
            tree[i].v = min(tree[i].v, diff);
            return;
        }

        ll m = (s + e) >> 1;
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
        tree[i].v = max(tree[tree[i].l].v, tree[tree[i].r].v);
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        if (i == 0 || e < l || s > r)
            return -0x3f3f3f3f3f3f3f3f;
        else if (l <= s && e <= r)
            return tree[i].v;
        else
        {
            ll m = (s + e) >> 1;
            return max(_query(tree[i].l, s, m, l, r), _query(tree[i].r, m + 1, e, l, r));
        }
    }

public:
    ll s, e;
    DynamicMaxSegmentTree(int cap = 2000000)
    {
        tree.reserve(cap);
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 0;
        this->e = (ll)1e9 + 5;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }
};

class DynamicMinSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll v;
        Node() : l(0), r(0), v(0x3f3f3f3f3f3f3f3f) {}
    };
    vector<Node> tree;

    void _update_idx(int i, ll s, ll e, ll idx, ll diff)
    {
        if (s == e)
        {
            tree[i].v = diff;
            return;
        }

        ll m = (s + e) >> 1;
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
        tree[i].v = min(tree[tree[i].l].v, tree[tree[i].r].v);
    }

    ll _query(int i, ll s, ll e, ll l, ll r)
    {
        if (i == 0 || e < l || s > r)
            return 0x3f3f3f3f3f3f3f3f;
        else if (l <= s && e <= r)
            return tree[i].v;
        else
        {
            ll m = (s + e) >> 1;
            return min(_query(tree[i].l, s, m, l, r), _query(tree[i].r, m + 1, e, l, r));
        }
    }

public:
    ll s, e;
    DynamicMinSegmentTree(int cap = 2000000)
    {
        tree.reserve(cap);
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 0;
        this->e = (ll)1e9 + 5;
    }

    ll query(ll l, ll r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(ll idx, ll diff)
    {
        _update_idx(1, s, e, idx, diff);
    }
};

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

public:
    PersistentLiChaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
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

    void add_line(ll a, ll b)
    {
        add_line({a, b}, 0);
        idx++;
    }

    void delete_line()
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

class OfflineLiChaoTree
{
private:
    class LiChaoTree
    {
    private:
        struct Line
        {
            ll a, b;
            Line(ll a, ll b) : a(a), b(b) {}

            ll f(ll x)
            {
                return (ll)a * x + b;
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
        int s = -2e9, e = 2e9;
        LiChaoTree()
        {
            tree.push_back({-1, -1, s, e, Line(0, -INF)});
        }

        void add_line(Line new_line, int i = 0)
        {
            int xl = tree[i].xl, xr = tree[i].xr;
            int xm = ((ll)xl + xr) >> 1;

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
            int xm = ((ll)xl + xr) >> 1;
            if (x <= xm)
                return max(tree[i].line.f(x), query(x, tree[i].l));
            else
                return max(tree[i].line.f(x), query(x, tree[i].r));
        }

        Line query2(ll x, int i = 0)
        {
            if (i == -1)
                return Line(0, -INF);
            int xl = tree[i].xl, xr = tree[i].xr;
            int xm = ((ll)xl + xr) >> 1;
            if (x <= xm)
            {
                Line line = query2(x, tree[i].l);
                if (line.f(x) > tree[i].line.f(x))
                    return line;
                else
                    return tree[i].line;
            }
            else
            {
                Line line = query2(x, tree[i].r);
                if (line.f(x) > tree[i].line.f(x))
                    return line;
                else
                    return tree[i].line;
            }
        }
    };

    vector<LiChaoTree> tree;
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

        int m = ((ll)s + e) >> 1;
        insert(2 * i, s, m, l, r, value);
        insert(2 * i + 1, m + 1, e, l, r, value);
    }

    ll query(int i, int s, int e, int idx, ll x)
    {
        if (!(s <= idx && idx <= e))
            return -INF;

        if (s == e)
            return tree[i].query(x);

        int m = ((ll)s + e) >> 1;
        return max({tree[i].query(x), query(2 * i, s, m, idx, x), query(2 * i + 1, m + 1, e, idx, x)});
    }

public:
    OfflineLiChaoTree(int q) : q_idx(0), tree(4 * q) {}

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

    vector<ll> get_ans()
    {
        for (auto [l, r, a, b] : q)
            insert(1, 1, q_idx, l, (r == -1 ? q_idx : r), {a, b});

        for (auto [idx, x] : q2)
            ans.push_back(query(1, 1, q_idx, idx, x));

        return ans;
    }
};

class CentroidDecomposition
{
private:
    vector<vector<int>> adj;
    vector<int> sz, p;
    vector<bool> del;

    void dfs1(int s, int parent)
    {
        sz[s] = 1;
        for (auto e : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            dfs1(e, s);
            sz[s] += sz[e];
        }
    }

    int dfs2(int s, int parent, int cap)
    {
        for (auto e : adj[s])
        {
            if (del[e] || parent == e)
                continue;
            if (sz[e] > cap)
                return dfs2(e, s, cap);
        }
        return s;
    }

    void dfs3(int s, int parent)
    {
        dfs1(s, -1);
        s = dfs2(s, -1, sz[s] / 2);
        del[s] = true;
        p[s] = parent;

        for (auto e : adj[s])
        {
            if (!del[e])
            {
                dfs3(e, s);
            }
        }
    }
public:
    CentroidDecomposition(int n) : adj(n + 1), sz(n + 1), del(n + 1), p(n + 1) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> make_centroid_tree()
    {
        dfs3(1, 0);
        return p;
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

int readInt() {
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

class MinSegmentTree
{
private:
    vector<ll> tree;

public:
    MinSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), INF);
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
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0x3f3f3f3f3f3f3f3f;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

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

class LiChaoTree
{
private:
    struct Line
    {
        int idx;
        ll a, b;
        Line(ll a, ll b, int idx = -1) : a(a), b(b), idx(idx) {}

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
    };

    vector<Node> tree;
    void add_line(Line new_line, int i)
    {
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;

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

public:
    ll s = -2e9, e = 2e9;
    LiChaoTree()
    {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    void add_line(ll a, ll b)
    {
        add_line({a, b}, 0);
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

    Line query2(ll x, int i = 0)
    {
        if (i == -1)
            return Line(0, -INF);
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm)
        {
            Line line = query2(x, tree[i].l);
            if (line.f(x) > tree[i].line.f(x))
                return line;
            else
                return tree[i].line;
        }
        else
        {
            Line line = query2(x, tree[i].r);
            if (line.f(x) > tree[i].line.f(x))
                return line;
            else
                return tree[i].line;
        }
    }
};

struct FastMinCostMaxFlow
{
    struct Edge
    {
        int pos, cap, rev, cost;
    };

    int source, sink, sz;

    FastMinCostMaxFlow(int n)
        : ptr(n + 2), phi(n + 2), inque(n + 2), dis(n + 2), visit(n + 2), sz(n + 2), adj(n + 2)
    {
        source = 0;
        sink = n + 1;
    }

    vector<int> ptr, phi, inque, dis;
    vector<bool> visit;
    vector<vector<Edge>> adj;

    void add_edge(int u, int v, int cap, int cost)
    {
        adj[u].push_back({v, cap, (int)adj[v].size(), cost});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1, -cost});
    }

    void prep(int source, int sink)
    {
        fill(phi.begin(), phi.end(), INF);
        fill(dis.begin(), dis.end(), INF);
        queue<int> q;
        q.push(source);
        inque[source] = 1;
        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inque[s] = 0;
            for (auto &e : adj[s])
            {
                if (e.cap > 0 && phi[e.pos] > phi[s] + e.cost)
                {
                    phi[e.pos] = phi[s] + e.cost;
                    if (!inque[e.pos])
                    {
                        inque[e.pos] = 1;
                        q.push(e.pos);
                    }
                }
            }
        }

        for (int i = 0; i < sz; i++)
            for (auto &j : adj[i])
                if (j.cap > 0)
                    j.cost += phi[i] - phi[j.pos];

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push(pii(0, source));
        dis[source] = 0;
        while (!pq.empty())
        {
            auto l = pq.top();
            pq.pop();
            if (dis[l.second] != l.first)
                continue;
            for (auto &i : adj[l.second])
            {
                if (i.cap > 0 && dis[i.pos] > l.first + i.cost)
                {
                    dis[i.pos] = l.first + i.cost;
                    pq.push(pii(dis[i.pos], i.pos));
                }
            }
        }
    }
    int dfs(int pos, int sink, int flow)
    {
        visit[pos] = 1;

        if (pos == sink)
            return flow;

        for (; ptr[pos] < adj[pos].size(); ptr[pos]++)
        {
            auto &i = adj[pos][ptr[pos]];
            if (!visit[i.pos] && dis[i.pos] == i.cost + dis[pos] && i.cap > 0)
            {
                int ret = dfs(i.pos, sink, min(i.cap, flow));
                if (ret != 0)
                {
                    i.cap -= ret;
                    adj[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    pii mcmf()
    {
        prep(source, sink);
        for (int i = 0; i < sz; i++)
            dis[i] += phi[sink] - phi[source];
        int cost = 0, flow = 0;

        while (true)
        {
            fill(ptr.begin(), ptr.end(), 0);
            fill(visit.begin(), visit.end(), 0);

            int tmp = 0;
            while ((tmp = dfs(source, sink, 1e9)))
            {
                cost += dis[sink] * tmp;
                flow += tmp;
                fill(visit.begin(), visit.end(), 0);
            }

            tmp = 1e9;
            for (int i = 0; i < sz; i++)
            {
                if (!visit[i])
                    continue;
                for (auto &j : adj[i])
                    if (j.cap > 0 && !visit[j.pos])
                        tmp = min(tmp, (dis[i] + j.cost) - dis[j.pos]);
            }

            if (tmp > 1e9 - 200)
                break;

            for (int i = 0; i < sz; i++)
                if (!visit[i])
                    dis[i] += tmp;
        }
        return {cost, flow};
    }
};

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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
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
    bool flag, edge;
    vector<vector<int>> adj;
    vector<int> weight, parent, depth, num, idx, hld, num_end;
    SegmentTree Tree;

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

    void update_subtree(int i, ll diff)
    {
        init();
        Tree.update_range(1, 1, n, num[i], num_end[i], diff);
    }

    void update_path(int u, int v, ll diff)
    {
        init();
        int lca = LCA(u, v);
        _update_path(lca, u, diff, true);
        _update_path(lca, v, diff, edge);
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
        return _query(lca, u, true) + _query(lca, v, edge);
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

class FFT
{
private:
    typedef complex<double> cp;
    void fft(vector<cp> &a, bool flag)
    {
        int n = a.size(), j = 0;
        vector<cp> roots(n/2);
        for(int i = 1; i < n; i++)
        {
            int bit = (n >> 1);
            while(j >= bit)
                j -= bit, bit >>= 1;
            j += bit;
            if(i < j)
                swap(a[i], a[j]);
        }

        double ang = 2 * acos(-1) / n * (flag ? -1 : 1);
        for(int i = 0; i < n/2; i++)
            roots[i] = cp(cos(ang * i), sin(ang * i));

        for(int i = 2; i <= n; i <<= 1)
        {
            int step = n / i;
            for(int j = 0; j < n; j += i)
            {
                for(int k = 0; k < i/2; k++)
                {
                    cp u = a[j+k], v = a[j+k+i/2] * roots[step * k];
                    a[j+k] = u+v;
                    a[j+k+i/2] = u-v;
                }
            }
        }
        if(flag)
            for(int i = 0; i < n; i++)
                a[i] /= n;
    }
public:
    vector<ll> multiply(vector<ll> &f, vector<ll> &g)
    {
        vector<cp> fv(f.begin(), f.end()), fw(g.begin(), g.end());
        int n = 1;
        while(n < max(f.size(), g.size()))
            n <<= 1;
        n <<= 1;
        fv.resize(n);
        fw.resize(n);
        fft(fv, 0);
        fft(fw, 0);
        for(int i = 0; i < n; i++)
            fv[i] *= fw[i];
        fft(fv, 1);
        vector<ll> h(n);
        for(int i = 0; i < n; i++)
            h[i] = (ll)round(fv[i].real());
        while (h.size() > f.size() + g.size() - 1)
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
        return _query(r) - (l <= 0 ? 0 : _query(l - 1));
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
        Node() : v(0), l(0), r(0) {}
        int v, l, r;
    };
    vector<int> x;
    vector<Node> tree;
    vector<vector<pii>> y;
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
        tree[ret].l = make_tree(tree[cur].l, ys, ym, y, v);
        tree[ret].r = make_tree(tree[cur].r, ym + 1, ye, y, v);
        tree[ret].v = tree[tree[ret].l].v + tree[tree[ret].r].v;
        return ret;
    }

    int dfs(int ys, int ye)
    {
        int ret = tree.size();
        tree.push_back(Node());

        if (ys == ye)
        {
            tree[ret].v = 0;
            return ret;
        }

        int ym = (ys + ye) >> 1;
        tree[ret].l = dfs(ys, ym);
        tree[ret].r = dfs(ym + 1, ye);
        tree[ret].v = tree[tree[ret].l].v + tree[tree[ret].r].v;
        return ret;
    }

    int query(int cur, int ys, int ye, int yl, int yr)
    {
        if (ys > yr || ye < yl || !cur)
            return 0;
        else if ((yl <= ys && ye <= yr))
            return tree[cur].v;
        int ym = (ys + ye) >> 1;
        return query(tree[cur].l, ys, ym, yl, yr) + query(tree[cur].r, ym + 1, ye, yl, yr);
    }

    void init()
    {
        if (!flag)
            return;
        flag = false;
        x[xs] = dfs(ys, ye);

        for (auto [i, v] : y[xs])
            x[xs] = make_tree(x[xs], ys, ye, i, v);

        for (int i = 1; i <= xe; i++)
        {
            if (!y[i].empty())
                for (int j = 0; j < y[i].size(); j++)
                    x[i] = make_tree(x[(j == 0 ? i - 1 : i)], ys, ye, y[i][j].first, y[i][j].second);
            else
                x[i] = x[i - 1];
        }
    }

    int kth(int t1, int t2, int ys, int ye, int k)
    {
        int ym = (ys + ye) >> 1;

        if (ys == ye)
            return ys;

        if (tree[tree[t2].l].v - tree[tree[t1].l].v >= k)
            return kth(tree[t1].l, tree[t2].l, ys, ym, k);
        else
            return kth(tree[t1].r, tree[t2].r, ym + 1, ye, k - (tree[tree[t2].l].v - tree[tree[t1].l].v));
    }

public:
    // make_tree [0, x] x [0, y] segment tree
    PersistentSegmentTree(int x, int y) : xs(0), xe(x), ys(0), ye(y), x(x + 1), y(y + 1)
    {
        tree.push_back(Node());
    }

    // add point (x, y)
    void add_point(int x, int y, int v = 1)
    {
        this->y[x].push_back({y, v});
    }

    // query [xl, xr] x [yl, yr]
    int query(int xl, int xr, int yl, int yr)
    {
        init();
        if (xl == 0)
            return query(x[xr], ys, ye, yl, yr);
        else
            return query(x[xr], ys, ye, yl, yr) - query(x[xl - 1], ys, ye, yl, yr);
    }

    // find min(y) that satisfies query [xl, xr] x [0, y] >= k
    int kth(int xl, int xr, int k)
    {
        init();
        return kth((xl == 0 ? 0 : x[xl - 1]), x[xr], ys, ye, k);
    }
};

using ld = long double;
class ConvexHullTrick
{
private:
    int ptr = 0;
    struct Line
    {
        ll a, b;
        int idx;
        Line(ll a, ll b, int idx) : a(a), b(b), idx(idx) {}
        ll f(ll x) { return a * x + b; }
    };

    deque<Line> dq;

    ld cross_point(Line x, Line y)
    {
        if (x.a == y.a)
            return (x.b > y.b ? INF : -INF);
        return (ld)(x.b - y.b) / (y.a - x.a);
    }

    void add_line(Line ins)
    {
        while (dq.size() >= 2 && cross_point(dq[dq.size() - 2], dq.back()) > cross_point(dq.back(), ins))
            dq.pop_back();

        dq.push_back(ins);
    }

public:
    void add_line(ll a, ll b, int idx = -1)
    {
        add_line(Line(a, b, idx));
    }

    ll query1(ll x)
    {
        while (ptr + 1 != dq.size() && cross_point(dq[ptr], dq[ptr + 1]) <= x)
            dq.pop_front();
        return dq[ptr].f(x);
    }

    Line query2(ll x)
    {
        while (ptr + 1 != dq.size() && cross_point(dq[ptr], dq[ptr + 1]) <= x)
            dq.pop_front();
        return dq[ptr];
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

    int ccw(const pll &a, const pll &b, const pll &c)
    {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        auto [x3, y3] = c;
        auto ret = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
        return (ret == 0 ? ret : ret / abs(ret));
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
                if (ccw(b, a, p) >= 0)
                {
                    if (ccw(b, a, p) == 0)
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

        ll m = (s + e) >> 1;
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
            ll m = (s + e) >> 1;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

    ll _kth(int i, ll s, ll e, ll sum)
    {
        if (s == e)
            return s;
        ll m = (s + e) >> 1;
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

        ll m = (s + e) >> 1;
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

        ll m = (s + e) >> 1;

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
            ll m = (s + e) >> 1;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

    ll _kth(int i, ll s, ll e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        ll m = (s + e) >> 1;
        if (tree[tree[i].l].value < sum)
            return _kth(tree[i].r, m + 1, e, sum - tree[tree[i].l].value);
        else
            return _kth(tree[i].l, s, m, sum);
    }

public:
    ll s, e;
    DynamicSegmentTree(int cap = 2000000)
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
    Tree(int n)
    {
        this->n = n;
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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
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
            int m = (s + e) >> 1;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
    int kth(int i, int s, int e, ll sum)
    {
        update_lazy(i, s, e);
        if (s == e)
            return s;
        int m = (s + e) >> 1;
        update_lazy(2 * i, s, m);
        update_lazy(2 * i + 1, m + 1, e);
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

int parent[200005];
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
memset(parent, -1, sizeof(parent));

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
    
    // [1..a] x [1..b] bipartite graph's minimum vertex cover 
    pair<vector<int>, vector<int>> minimum_vertex_cover(int a, int b)
    {
        vector<bool> visit(a + b + 1), matched(a + b + 1);
        vector<int> A, B;
        queue<int> q;

        for (auto &e : adj[source])
        {
            if (e.cap == 1)
            {
                if (!(matched[e.to] = e.flow))
                {
                    visit[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        
        while (!q.empty())
        {
            int i = q.front();
            q.pop();

            for (auto &e : adj[i])
            {
                if (1 <= e.to && e.to <= a + b && !visit[e.to] && e.cap > e.flow)
                {
                    q.push(e.to);
                    visit[e.to] = true;
                }
            }
        }
        
        for (int i = 1; i <= a; i++)
            if (!visit[i])
                A.push_back(i);
        for (int i = a + 1; i <= a + b; i++)
            if (visit[i])
                B.push_back(i - a);

        return {A, B};
    }
};