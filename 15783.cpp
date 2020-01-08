#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

vector<int> temp, st;
vector<int> adj[100005], rev_adj[100005], new_adj[100005];

bool visit[100005];
int node_num[100005], indegree[100005];
int cnt, ans;

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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        sort(rev_adj[i].begin(), rev_adj[i].end());

        if (!visit[i])
            dfs(i, true);
    }

    memset(visit, 0, sizeof(visit));

    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        if (!visit[s])
        {
            dfs(s, false);

            for (auto i : temp)
                node_num[i] = cnt;
            temp.clear();

            cnt++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (auto j : adj[i])
        {
            if (node_num[i] != node_num[j])
                indegree[node_num[j]]++;
        }
    }

    for (int i = 0; i < cnt; i++)
    {
        if (!indegree[i])
            ans++;
    }

    cout << ans;
}