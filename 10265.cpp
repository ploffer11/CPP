#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

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

int dp[1005][1005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    StronglyConnectedComponent SCC(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        SCC.add_edge(i, x);
    }

    SCC.make_scc();

    vector<int> sz;
    for (auto &i : SCC.scc_node)
        sz.push_back(i.size());

    dp[0][0] = 1;
    for (int i = 1; i <= sz.size(); i++)
    {
        auto value = sz[i - 1];
        for (int j = 0; j <= k; j++)
            dp[i][j] = dp[i - 1][j];

        for (int j = value; j <= k; j++)
            dp[i][j] |= dp[i - 1][j - value];

        for (int j = 0; j <= k; j++)
            cout << dp[i][j] << " ";
        cout << "\n";
    }

    for (int i = k; i >= 0; i--)
    {
        if (dp[sz.size()][i])
        {
            cout << i;
            return 0;
        }
    }
}