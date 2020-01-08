#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 405;

// visit[i][j][k] : i행 j열이 k를 보고있을때 도착할떄까지 걸린 시간
// 0: right
// 1: up
// 2: left
// 3: down

int board[MAX][MAX], visit[MAX][MAX][4];
int k, r, c, sr, sc;

int dr[] = {0, -1, 0, 1};
int dc[] = {1, 0, -1, 0};

bool check(int R, int C)
{
    return (1 <= R && R <= r && 1 <= C && C <= c);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> r >> c >> k >> sr >> sc;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> board[i][j];

    sr++;
    sc++;

    using t = tuple<int, int, int>;

    queue<t> q;
    q.push({k, sr, sc});
    visit[sr][sc][(board[sr][sc] + k) % 4] = k;

    while (!q.empty())
    {
        auto [k, r, c] = q.front();
        q.pop();

        int d = (board[r][c] + k) % 4;
        int R = r + dr[d], C = c + dc[d];

        if (check(R, C) && !visit[R][C][(board[R][C] + k + 1) % 4])
        {
            visit[R][C][(board[R][C] + k + 1) % 4] = k + 1;
            q.push({k + 1, R, C});
        }

        if (!visit[r][c][(board[r][c] + k + 1) % 4])
        {
            visit[r][c][(board[r][c] + k + 1) % 4] = k + 1;
            q.push({k + 1, r, c});
        }
    }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            int ret = INF;
            for (int k = 0; k < 4; k++)
                ret = (visit[i][j][k] == 0 ? ret : min(ret, visit[i][j][k]));
            cout << ret << " ";
        }
        cout << '\n';
    }
}