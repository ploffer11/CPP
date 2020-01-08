#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int N = 100005;

vector<int> adj[N], rev_adj[N];
vector<int> st, temp;

int parent[N], indegree[N];
bool visit[N];

void dfs(int s, bool flag)
{
    if (visit[s])
        return;

    visit[s] = true;
    for (auto e : (flag ? adj[s] : rev_adj[s]))
        dfs(e, flag);

    (flag ? st : temp).push_back(s);
}

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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        memset(parent, -1, sizeof(parent));
        memset(indegree, 0, sizeof(indegree));
        int n, m;
        cin >> n >> m;

        vector<pii> edges;
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            rev_adj[v].push_back(u);
            edges.push_back({u, v});
        }

        for (int i = 0; i < n; i++)
        {
            sort(adj[i].begin(), adj[i].end());
            sort(rev_adj[i].begin(), rev_adj[i].end());
        }

        memset(visit, 0, sizeof(visit));
        for (int i = 0; i < n; i++)
            dfs(i, true);

        memset(visit, 0, sizeof(visit));
        while (!st.empty())
        {
            dfs(st.back(), false);
            st.pop_back();

            for (int i = 1; i < temp.size(); i++)
                uni(temp[0], temp[i]);

            temp.clear();
        }

        for (auto [u, v] : edges)
        {
            if (find(u) != find(v))
                indegree[find(v)]++;
        }

        set<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (!indegree[find(i)])
                ans.insert(find(i));
        }

        if (ans.size() == 1)
        {
            for (auto j : ans)
            {
                for (int i = 0; i < n; i++)
                    if (find(i) == j)
                        cout << i << '\n';
            }
        }

        else
        {
            cout << "Confused\n";
        }

        cout << '\n';
        for (int i = 0; i < n; i++)
        {
            adj[i].clear();
            rev_adj[i].clear();
        }
    }
}