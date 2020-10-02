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

#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin(); };

class OfflineDynamicConnectivity
{
private:
    enum { ADD, DELETE, QUERY };
    int n, q, q_cnt = 0;
    vector<tuple<int, int, int, int>> st, upd_vt;
    vector<vector<pii>> tree;
    vector<pii> Q;
    vector<int> parent, rank, ans;
    
    int find(int me)
    {
        if (parent[me] < 0)
            return me;
        else 
            return find(parent[me]);
    }
    
    bool uni(int u, int v)
    {
        u = find(u), v = find(v);
        if (u == v)
            return false;
        if (rank[u] < rank[v])
            swap(u, v);
        
        st.push_back({v, parent[v], u, rank[u]});
        parent[v] = u;
        rank[u] = max(rank[v], rank[u] + 1);
        return true;
    }
    
    void update(int i, int s, int e, int l, int r, pii v)
    {
        if (l > e || r < s)
            return;
            
        if (l <= s && e <= r)
        {
            tree[i].push_back(v);
            return;
        }
        int m = (s + e) >> 1;
        update(i << 1, s, m, l, r, v);
        update(i << 1 | 1, m + 1, e, l, r, v);
    }
    
    void rollback(int k)
    {
        while (k--)
        {
            auto [w, x, y, z] = st.back();
            st.pop_back();
            parent[w] = x;
            rank[y] = z;
        }
    }
    
    
    void solve(int i, int s, int e)
    {
        int k = 0;
        
        for (auto [u, v] : tree[i])
            if (uni(u, v))
                k++;
        
        if (s == e)
        {
            if (Q[s].first != -1)
                ans.push_back(find(Q[s].first) == find(Q[s].second));
            
            rollback(k);
            return;
        }
        
        int m = (s + e) >> 1;
        solve(i << 1, s, m);
        solve(i << 1 | 1, m + 1, e);
        rollback(k);
    }

public:
    OfflineDynamicConnectivity(int n, int q) : n(n), q(q), parent(n + 1, -1), rank(n + 1, 1), tree(4 * (q + 1)), Q(q + 1, pii(-1, -1)) {}
    
    void add_edge(int u, int v)
    {
        upd_vt.push_back({min(u, v), max(u, v), ++q_cnt, ADD});
    }
    
    void delete_edge(int u, int v)
    {
        upd_vt.push_back({min(u, v), max(u, v), ++q_cnt, DELETE});
    }
    
    void query(int u, int v)
    {
        Q[++q_cnt] = {min(u, v), max(u, v)};
    }
    
    vector<int> get_ans()
    {
        vector<tuple<int, int, int, int>> edge;
        sort(upd_vt.begin(), upd_vt.end());
        
        for (int i = 0; i < upd_vt.size() - 1; i++)
        {
            auto [u1, v1, idx1, q1] = upd_vt[i];
            auto [u2, v2, idx2, q2] = upd_vt[i + 1];
            
            if (u1 == u2 && v1 == v2)
            {
                if (q1 == ADD && q2 == DELETE)
                    edge.push_back({u1, v1, idx1, idx2});
            }
            else if (q1 == ADD)
            {
                edge.push_back({u1, v1, idx1, q});
            }
        }
        
        auto [u, v, idx, x] = upd_vt.back();
        if (x == ADD)
            edge.push_back({u, v, idx, q});
            
        for (auto [u, v, l, r] : edge)
            update(1, 1, q, l, r, pii(u, v));
        
        solve(1, 1, q);
        return ans;
    }
};

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;
    
    OfflineDynamicConnectivity ODC(n, q);
    
    while (q--)
    {
        int c, u, v;
        cin >> c >> u >> v;
        if (c == 1)
            ODC.add_edge(u, v);
        else if (c == 2)
            ODC.delete_edge(u, v);
        else 
            ODC.query(u, v);
    }
    
    for (auto i : ODC.get_ans())
    {
        cout << i << "\n";
    }
}