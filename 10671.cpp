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

struct StronglyConnectedComponent
{
    vector<vector<int>> adj, rev_adj, new_adj, scc_node;
    vector<int> st, temp, visit, scc;
    vector<pii> edge;
    int scc_cnt = 0, n;

    StronglyConnectedComponent(int n)
        : n(n), scc_node(n + 1), adj(n + 1), rev_adj(n + 1), new_adj(n + 1), visit(n + 1), scc(n + 1)
    {
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

    vector<int> dp1, dp2, near;
    int my_scc;
    void solve()
    {
        my_scc = scc[1];

        dp1.resize(scc_cnt + 1, -1);
        dp2.resize(scc_cnt + 1, -1);

        dp1[my_scc] = scc_node[my_scc].size();
        dp2[my_scc] = 0;

        for (auto i : st)
            for (auto j : new_adj[i])
                if (dp2[j] != -1)
                    dp2[i] = max(dp2[i], dp2[j] + (int)scc_node[i].size());

        reverse(st.begin(), st.end());

        for (auto i : st)
            for (auto j : new_adj[i])
                if (dp1[i] != -1)
                    dp1[j] = max(dp1[j], dp1[i] + (int)scc_node[j].size());

        int ans = 0;

        for (int i = 1; i <= scc_cnt; i++)
        {
            for (auto j : new_adj[i])
            {
                ans = max(ans, (dp2[i] == -1 ? -INF : dp2[i]) + (dp1[j] == -1 ? -INF : dp1[j]));
            }
        }
        cout << ans;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    StronglyConnectedComponent SCC(n);
    for (int x, y; m--;)
    {
        cin >> x >> y;
        SCC.add_edge(x, y);
    }

    SCC.make_scc();
    SCC.make_dag();
    SCC.solve();
}