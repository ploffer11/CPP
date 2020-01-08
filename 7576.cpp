#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using pii = pair<int, int>;
using t = tuple<int, int, int>;

int r, c;
int board[1005][1005], visit[1005][1005];

int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> c >> r;

    queue<t> q;
    int total_tomato = 0, ripen_tomato = 0, ans = -1;

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> board[i][j];
            total_tomato += (board[i][j] >= 0);
            if (board[i][j] == 1)
                q.push({0, i, j});
        }
    }

    while (!q.empty())
    {
        auto [depth, a, b] = q.front();
        q.pop();
        ans = max(ans, depth);
        ripen_tomato++;

        for (int i = 0; i < 4; i++)
        {
            int R = a + dr[i], C = b + dc[i];
            if (1 <= R && R <= r && 1 <= C && C <= c && !board[R][C] && !visit[R][C])
            {
                visit[R][C] = true;
                q.push({depth + 1, R, C});
            }
        }
    }

    if (total_tomato - ripen_tomato)
        cout << -1;

    else
        cout << ans;
}