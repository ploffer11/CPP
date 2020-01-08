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

class StronglyConnectedComponent
{
private:
    vector<vector<int>> adj, rev_adj;
    vector<int> st, temp, visit, scc;
    vector<pii> edge;
    int scc_cnt = 0, n;

public:
    StronglyConnectedComponent(int n) : n(n)
    {
        adj.resize(n + 1);
        rev_adj.resize(n + 1);
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
                    scc[i] = scc_cnt;
                temp.clear();
            }
        }
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
}