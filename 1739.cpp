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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m, q;
        cin >> n >> m >> q;
        TwoSatisfiability sat2(n + m);

        while (q--)
        {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            if (r1 == r2 && c1 == c2)
                continue;
            else if (r1 == r2 && c1 < c2)
                sat2.add_edge(r1, r1);
            else if (r1 == r2 && c1 > c2)
                sat2.add_edge(-r1, -r1);
            else if (c1 == c2 && r1 < r2)
                sat2.add_edge(n + c1, n + c1);
            else if (r1 == r2 && r1 > r2)
                sat2.add_edge(-n - c1, -n - c1);
            else
            {
                int a, b, c, d;
                if (r1 < r2 && c1 < c2)
                    a = r1, b = n + c2, c = r2, d = n + c1;
                else if (r1 > r2 && c1 < c2)
                    a = r1, b = -n - c2, c = r2, d = -n - c1;
                else if (r1 < r2 && c1 > c2)
                    a = -r1, b = n + c2, c = -r2, d = n + c1;
                else if (r1 > r2 && c1 > c2)
                    a = -r1, b = -n - c2, c = -r2, d = -n - c1;
                sat2.add_edge(a, c);
                sat2.add_edge(a, d);
                sat2.add_edge(b, c);
                sat2.add_edge(b, d);
            }
        }

        cout << (sat2.satisfy() ? "Yes\n" : "No\n");
    }
}