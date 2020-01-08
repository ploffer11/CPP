#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;

vector<int> adj[10005];
int board[100][100];
int match[10005], visit[10005];

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

    int T;
    cin >> T;
    while (T--)
    {
        int r, c;
        cin >> r >> c;

        int cnt = 0;

        vector<int> group1, group2;
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                char x;
                cin >> x;
                if (x == '.')
                {
                    board[i][j] = ++cnt;
                    (j % 2 == 1 ? group1 : group2).push_back(cnt);
                }
            }
        }

        int dr[] = {-1, 0, 1, -1, 0, 1}, dc[] = {-1, -1, -1, 1, 1, 1};
        for (int i = 1; i <= r; i++)
        {
            for (int j = 2; j <= c; j += 2)
            {
                for (int k = 0; k < 6; k++)
                {
                    int R = i + dr[k], C = j + dc[k];
                    if (board[i][j] && board[R][C])
                        adj[board[R][C]].push_back(board[i][j]);
                }
            }
        }

        int ans = cnt;
        for (auto i : group1)
        {
            for (auto j : group1)
                visit[j] = false;

            if (dfs(i))
                ans--;
        }

        cout << ans << endl;

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                board[i][j] = 0;

        for (auto i : group1)
            adj[i].clear();

        for (int i = 1; i <= cnt; i++)
            match[i] = visit[i] = false;
    }
}