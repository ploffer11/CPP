#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

bool visit[10005];

int ans = 0;
vector<vector<int>> scc, adj, rev_adj;
vector<int> temp;

stack<int> st;

void dfs_1(int s)
{
    visit[s] = true;
    for (auto e : adj[s])
    {
        if (!visit[e])
            dfs_1(e);
    }

    st.push(s);
}

void dfs_2(int s)
{
    visit[s] = true;
    temp.push_back(s);

    for (auto e : rev_adj[s])
    {
        if (!visit[e])
            dfs_2(e);
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int v, e;
    cin >> v >> e;

    adj.resize(v + 1);
    rev_adj.resize(v + 1);
    scc.resize(v + 1);

    while (e--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    for (int i = 1; i <= v; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        sort(rev_adj[i].begin(), rev_adj[i].end());

        if (!visit[i])
            dfs_1(i);
    }

    memset(visit, 0, sizeof(visit));

    while (!st.empty())
    {
        int s = st.top();
        // cout << "s: " << s << endl;
        st.pop();

        if (!visit[s])
        {
            dfs_2(s);
            sort(temp.begin(), temp.end());
            for (auto i : temp)
                scc[temp[0]].push_back(i);
            temp.clear();
            ans++;
        }
    }

    cout << ans << '\n';
    for (int i = 1; i <= v; i++)
    {
        if (!scc[i].empty())
        {
            for (auto j : scc[i])
                cout << j << " ";
            cout << "-1\n";
        }
    }
}