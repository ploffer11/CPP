#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int match[40010];
int board[205][205];
bool visit[205];
vector<int> adj[205];

bool dfs(int s)
{
    visit[s] = true;
    for (auto e : adj[s])
    {
        if (!match[e] || (!visit[match[e]] && dfs(match[e])))
        {
            match[e] = s;
            return true;
        }
    }
    return false;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    while (k--)
    {
        int i, j;
        cin >> i >> j;
        board[i][j] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (board[i][j])
                adj[i].push_back(j);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(visit, 0, sizeof(visit));
        if (dfs(i))
            ans++;
    }

    cout << n + m - ans;
}