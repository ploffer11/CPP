#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int n;
int visit[2005], parent[2005], finish[2005];

vector<vector<int>> adj;

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

int bfs(int s)
{
    memset(visit, 0, sizeof(visit));
    int ret = 0;

    queue<pii> q;
    q.push({s, 1});
    visit[s] = true;

    while (!q.empty())
    {
        auto [s, color] = q.front();
        q.pop();

        ret += color;
        for (auto e : adj[s])
        {
            if (!visit[e])
            {
                visit[e] = true;
                q.push({e, !color});
            }
        }
    }

    int sz = -parent[find(s)];
    finish[find(s)] = true;
    return max(ret, sz - ret);
}

int main()
{
    memset(parent, -1, sizeof(parent));

    cin >> n;
    adj.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        string inp;
        cin >> inp;

        for (int j = 0; j < n; j++)
        {
            if (inp[j] == '1')
            {
                adj[i].push_back(j + 1);
                adj[j + 1].push_back(i);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int j = find(i);
        if (!finish[j])
        {
            ans += bfs(j);
        }
    }

    cout << ans;
}