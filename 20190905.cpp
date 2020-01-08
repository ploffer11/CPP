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

bool cycle = false;
bool use[5005];
int visit[5005];
pii edge[5005];
vector<pii> adj[5005], rev_adj[5005];

int parent[5005];
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

void dfs(int s)
{
    for (auto [e, i] : adj[s])
    {
        if (!visit[e])
        {
            uni(s, e);
            visit[e] = visit[s] + 1;
            use[i] = true;
            dfs(e);
        }
    }
}

vector<int> st, temp;
void dfs_2(int s, bool flag)
{
    visit[s] = true;
    for (auto [e, _] : (flag ? adj[s] : rev_adj[s]))
    {
        if (!visit[e])
            dfs_2(e, flag);
    }
    (flag ? st : temp).push_back(s);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        edge[i] = {u, v};
        adj[u].push_back({v, i});
        rev_adj[v].push_back({u, i});
    }

    for (int i = 1; i <= n; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        sort(rev_adj[i].begin(), rev_adj[i].end());
    }

    for (int i = 1; i <= n; i++)
        if (!visit[i])
            dfs_2(i, true);

    memset(visit, 0, sizeof(visit));
    while (!st.empty())
    {
        int s = st.back();
        st.pop_back();

        if (!visit[s])
            dfs_2(s, false);

        if (temp.size() >= 2)
        {
            cycle = true;
            break;
        }

        temp.clear();
    }

    memset(visit, 0, sizeof(visit));

    for (int i = 1; i <= n; i++)
    {
        if (!visit[i])
        {
            visit[i] = 1;
            dfs(i);
        }
    }

    //cout << " cycle: " << cycle << "\n";
    if (!cycle)
    {
        cout << "1\n";
        while (m--)
            cout << "1 ";
        return 0;
    }

    cout << "2\n";

    for (int i = 1; i <= m; i++)
    {
        if (use[i])
            cout << "1 ";

        else
        {
            auto [u, v] = edge[i];
            if (find(u) != find(v))
                cout << "1 ";
            else
            {
                if (visit[u] > visit[v])
                    cout << "2 ";
                else if (visit[u] < visit[v])
                    cout << "1 ";
                else if (u < v)
                    cout << "1 ";
                else
                    cout << "2 ";
            }
        }
    }
}