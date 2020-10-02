class OfflineDynamicConnectivity
{
private:
    enum { ADD, DELETE, QUERY };
    int n, q, q_cnt = 0;
    vector<int> parent, rank, st, ans;
    vector<pii> Q;
    vector<vector<pii>> tree;
    vector<tuple<int, int, int, int>> q_vt;
    vector<tuple<int, int, int, int>> upd_vt;
    
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
        
        parent[u] += parent[v];
        parent[v] = u;
        rank[v] = max(rank[v], rank[u] + 1);
        st.push_back({v, parent[v]});
        return true;
    }
    
    void update(int i, int s, int e, int l, int r, pii v)
    {
        if (l > e || r < s)
            return;
            
        if (l <= s && e <= r)
        {
            tree.push_back(v);
            return;
        }
        
        int m = (s + e) >> 1;
        update(i << 1, s, m, l, r, v);
        update(i << 1 | 1, m + 1, e, l, r, v);
    }
    
    int update(int i, int s, int e, int l, int r)
    {
        if (!(s <= l && r <= e))
            return 0;
        int ret = 0;
        for (auto [u, v] : tree)
            if (uni(u, v))
                ret++;
        return ret + update(i << 1, s, m, l, r) + update(i << 1 | 1, m + 1, e, l, r);
    }
    
    
    void solve(int s, int e)
    {
        int k = update(1, 1, q, s, e);
        
        if (s == e)
        {
            if (Q[s].first != -1)
                ans[s].push_back(Q[s].first == Q[s].second);
            return;
        }
        
        int m = (s + e) >> 1;
        solve(s, m);
        solve(m + 1, e);
        
        while (k--)
        {
            auto [x, y] = st.back();
            st.pop_back();
            parent[x] = y;
        }
    }

public:
    OfflineDynamicConnectivity(int n, int q) : n(n), q(q), parent(n + 1, -1), rank(n + 1, 1), tree(4 * (n + 1)), Q(q + 1, pii(-1, -1)), q_vt(q + 1) {}
    
    void add_edge(int u, int v)
    {
        upd_vt.push_back({u, v, ++q_cnt, ADD});
        
    }
    
    void delete_edge(int u, int v)
    {
        upd_vt.push_Back({u, v, ++q_cnt, DELETE});
    }
    
    void query(int u, int v)
    {
        Q[++q_cnt] = {u, v};
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
        
        solve(1, q);
        return ans;
    }
};