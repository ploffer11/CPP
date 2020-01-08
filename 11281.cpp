#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int cnt;
int boolean[20005];
int group[20005];
bool visit[20005];

vector<int> scc[20005];
vector<int> adj[20005], rev_adj[20005], new_adj[20005];
vector<int> temp, st;

void dfs(int s, bool flag)
{
    visit[s] = true;

    for (auto e : (flag ? adj[s] : rev_adj[s]))
        if (!visit[e])
            dfs(e, flag);

    (flag ? st : temp).push_back(s);
}

void topological_sort(int s)
{
    visit[s] = true;
    for (auto e : new_adj[s])
        if (!visit[e])
            topological_sort(e);
    st.push_back(s);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(boolean, -1, sizeof(boolean));

    vector<pii> edges;
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;

        adj[(a < 0 ? -a : a + n)].push_back((b < 0 ? -b + n : b));
        adj[(b < 0 ? -b : b + n)].push_back((a < 0 ? -a + n : a));

        edges.push_back({(a < 0 ? -a : a + n), (b < 0 ? -b + n : b)});
        edges.push_back({(b < 0 ? -b : b + n), (a < 0 ? -a + n : a)});

        rev_adj[(b < 0 ? -b + n : b)].push_back((a < 0 ? -a : a + n));
        rev_adj[(a < 0 ? -a + n : a)].push_back((b < 0 ? -b : b + n));
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        sort(rev_adj[i].begin(), rev_adj[i].end());
    }

    for (int i = 1; i <= 2 * n; i++)
    {
        if (!visit[i])
            dfs(i, true);
    }

    memset(visit, 0, sizeof(visit));
    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        if (!visit[s])
            dfs(s, false);

        if (!temp.empty())
        {
            int c = ++cnt;
            for (auto i : temp)
            {
                scc[c].push_back(i);
                group[i] = c;
            }

            temp.clear();
        }
    }

    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        if (group[i] == group[i + n])
            flag = false;
    }

    cout << (flag ? 1 : 0) << '\n';
    if (flag)
    {
        for (auto [u, v] : edges)
            if (group[u] != group[v])
                new_adj[group[u]].push_back(group[v]);

        memset(visit, 0, sizeof(visit));
        for (int i = 1; i <= 2 * n; i++)
            if (!visit[group[i]])
                topological_sort(group[i]);

        reverse(st.begin(), st.end());
        for (auto i : st)
        {
            for (auto node : scc[i])
            {
                //cout << num << " - " << node << endl;
                bool flag = (node > n ? true : false);
                node = (node > n ? node - n : node);
                if (boolean[node] == -1)
                    boolean[node] = flag;
            }
        }
        for (int i = 1; i <= n; i++)
            cout << boolean[i] << " ";
    }
}