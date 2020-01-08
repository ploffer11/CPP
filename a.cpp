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



struct FastMinCostMaxFlow
{
    struct edg
    {
        int pos, cap, rev, cost;
    };
    const int INF = 0x3f3f3f3f;
    int src, sink, sz;

    FastMinCostMaxFlow(int n) : ptr(n + 2), phi(n + 2), inque(n + 2), dist(n + 2), vis(n + 2), sz(n + 2), gph(n + 2)
    {
        src = 0;
        sink = n + 1;
    }

    vector<int> ptr, phi, inque, dist;
    vector<bool> vis;
    vector<vector<edg>> gph;

    void add_edge(int s, int e, int x, int c)
    {
        gph[s].push_back({e, x, (int)gph[e].size(), c});
        gph[e].push_back({s, 0, (int)gph[s].size() - 1, -c});
    }
    void prep(int src, int sink)
    {
        fill(phi.begin(), phi.end(), INF);
        fill(dist.begin(), dist.end(), INF);
        queue<int> que;
        que.push(src);
        inque[src] = 1;
        while (!que.empty())
        {
            int x = que.front();
            que.pop();
            inque[x] = 0;
            for (auto &i : gph[x])
            {
                if (i.cap > 0 && phi[i.pos] > phi[x] + i.cost)
                {
                    phi[i.pos] = phi[x] + i.cost;
                    if (!inque[i.pos])
                    {
                        inque[i.pos] = 1;
                        que.push(i.pos);
                    }
                }
            }
        }
        for (int i = 0; i < sz; i++)
        {
            for (auto &j : gph[i])
            {
                if (j.cap > 0)
                    j.cost += phi[i] - phi[j.pos];
            }
        }
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push(pii(0, src));
        dist[src] = 0;
        while (!pq.empty())
        {
            auto l = pq.top();
            pq.pop();
            if (dist[l.second] != l.first)
                continue;
            for (auto &i : gph[l.second])
            {
                if (i.cap > 0 && dist[i.pos] > l.first + i.cost)
                {
                    dist[i.pos] = l.first + i.cost;
                    pq.push(pii(dist[i.pos], i.pos));
                }
            }
        }
    }
    int dfs(int pos, int sink, int flow)
    {
        vis[pos] = 1;
        if (pos == sink)
            return flow;
        for (; ptr[pos] < gph[pos].size(); ptr[pos]++)
        {
            auto &i = gph[pos][ptr[pos]];
            if (!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0)
            {
                int ret = dfs(i.pos, sink, min(i.cap, flow));
                if (ret != 0)
                {
                    i.cap -= ret;
                    gph[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int cost()
    {
        prep(src, sink);
        for (int i = 0; i < sz; i++)
            dist[i] += phi[sink] - phi[src];
        int ret = 0;
        while (true)
        {
            fill(ptr.begin(), ptr.end(), 0);
            fill(vis.begin(), vis.end(), 0);

            int tmp = 0;
            while ((tmp = dfs(src, sink, 1e9)))
            {
                ret += dist[sink] * tmp;
                fill(vis.begin(), vis.end(), 0);
            }
            tmp = 1e9;
            for (int i = 0; i < sz; i++)
            {
                if (!vis[i])
                    continue;
                for (auto &j : gph[i])
                {
                    if (j.cap > 0 && !vis[j.pos])
                    {
                        tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
                    }
                }
            }
            if (tmp > 1e9 - 200)
                break;
            for (int i = 0; i < sz; i++)
            {
                if (!vis[i])
                    dist[i] += tmp;
            }
        }
        return ret;
    }
};
char a[20];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    string a;
    getline(cin, a);
}
