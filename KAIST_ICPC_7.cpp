#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pvi = pair<vector<int>, int>;
const int INF = 1987654321;
const int MOD = 1e9 + 7;
const int MAX = 250'005;

vector<int> lex[MAX];
vector<pii> adj[MAX];
vector<int> adj2[MAX];
bool finish[MAX], visit[MAX];

void dijk(int s, int t)
{
    for (int i = 1; i <= MAX; i++)
        lex[i] = {INF};

    priority_queue<pvi, vector<pvi>, greater<pvi>> pq;
    lex[s] = {};
    pq.push({{}, s});

    while (!pq.empty())
    {
        auto [vt, node] = pq.top();
        pq.pop();

        cout << node << " -> ";
        for (auto i : vt)
            cout << i << " ";
        cout << endl;

        if (lex[t].size() > 100'0000)
            return;

        for (auto [e, color] : adj[node])
        {
            vt.push_back(color);
            if (lex[e] > vt)
            {
                lex[e] = vt;
                pq.push({vt, e});
            }
            vt.pop_back();
        }
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj2[u].push_back(v);
    }

    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        for (auto e : adj2[s])
        {
            if (!visit[e])
            {
                visit[e] = true;
                q.push(e);
            }
        }
    }
    if (!visit[t])
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    dijk(s, t);

    if (lex[t].size() > 100'0000)
    {
        cout << "TOO LONG";
        return 0;
    }

    for (auto i : lex[t])
        cout << i << " ";
}
