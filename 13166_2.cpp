#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

vector<pii> adj[200'005];
bool visit[400'005];
int match[400'005];

bool dfs(int s, int k)
{
    visit[s] = true;
    for (auto [e, cost] : adj[s])
        if (cost <= k && (!match[e] || (!visit[match[e]] && dfs(match[e], k))))
            return !!(match[e] = s);

    return false;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        adj[i].push_back({a, b});
        adj[i].push_back({c, d});
    }

    int MAX = 1'000'005;
    int s = 0, e = MAX;

    while (s <= e)
    {
        int m = (s + e) / 2;
        int f = 0;

        memset(match, 0, sizeof(match));
        for (int i = 1; i <= n; i++)
        {
            memset(visit, 0, sizeof(visit));
            if (dfs(i, m))
                f++;
        }

        if (f == n)
            e = m - 1;
        else
            s = m + 1;
    }

    //cout << s << " " << e << '\n';
    cout << (s >= MAX ? -1 : s);
}