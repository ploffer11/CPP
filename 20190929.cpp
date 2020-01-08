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

bool visit[100005];
vector<int> adj[100'005];
vector<pii> edge;

vector<int> reach(int s)
{
    vector<int> ret;

    for (auto e : adj[s])
        ret.push_back(e);

    return ret;
}

int parent[100005];
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

int num[100'005], degree[100'005];
bool flag[100'005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge.push_back({u, v});
        uni(u, v);
    }

    if (-parent[find(1)] != n)
    {
        cout << "-1";
        return 0;
    }

    vector<int> vt1 = reach(1);
    vector<int> vt2 = reach(vt1[0]);
    sort(vt1.begin(), vt1.end());
    sort(vt2.begin(), vt2.end());

    vector<int> group1(2 * n);
    vector<int> group2;
    vector<int> group3(2 * n);

    group3.erase(set_intersection(vt1.begin(), vt1.end(), vt2.begin(), vt2.end(), group3.begin()), group3.end());
    group1.erase(set_symmetric_difference(vt1.begin(), vt1.end(), group3.begin(), group3.end(), group1.begin()), group1.end());

    for (auto i : group1)
        flag[i] = true;

    for (auto i : group3)
        flag[i] = true;

    for (int i = 1; i <= n; i++)
        if (!flag[i])
            group2.push_back(i);

    if (group1.size() == 0 || group2.size() == 0 || group3.size() == 0)
    {
        cout << "-1";
        return 0;
    }
    if (group1.size() + group2.size() + group3.size() != n)
    {
        cout << "-1";
        return 0;
    }

    for (auto i : group1)
        num[i] = 1;
    for (auto i : group2)
        num[i] = 2;
    for (auto i : group3)
        num[i] = 3;

    for (auto [u, v] : edge)
    {
        if (num[u] == num[v])
        {
            cout << "-1";
            return 0;
        }
        degree[u]++;
        degree[v]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (num[i] == 1 && adj[i].size() != group2.size() + group3.size())
        {
            cout << "-1";
            return 0;
        }
        if (num[i] == 2 && adj[i].size() != group1.size() + group3.size())
        {
            cout << "-1";
            return 0;
        }
        if (num[i] == 3 && adj[i].size() != group1.size() + group2.size())
        {
            cout << "-1";
            return 0;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << num[i] << " ";
}