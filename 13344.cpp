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

int n, m;
vector<pii> edge;
vector<int> adj[50005];
int parent[50005], indegree[50005];
bool inq[50005];

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

main()
{
    memset(parent, -1, sizeof(parent));
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;
    while (m--)
    {
        int a, c;
        char b;

        cin >> a >> b >> c;

        if (b == '>')
        {
            edge.push_back({a, c});
        }
        else if (b == '=')
        {
            uni(a, c);
        }
    }

    for (auto [u, v] : edge)
    {
        adj[find(u)].push_back(find(v));
        indegree[find(v)]++;
    }

    queue<int> q;
    vector<int> cp;
    for (int i = 0; i < n; i++)
    {
        cp.push_back(find(i));
        if (!indegree[find(i)] && !inq[find(i)])
        {
            inq[find(i)] = true;
            q.push(find(i));
        }
    }
    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());
    vector<int> vt;
    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        vt.push_back(s);

        for (auto e : adj[s])
        {
            if (--indegree[e] == 0)
            {
                q.push(e);
            }
        }
    }

    cout << (vt.size() != cp.size() ? "inconsistent" : "consistent");
}