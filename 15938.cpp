#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int _x1, _y1, x2, y2, t;
int board[405][405];
ll dp[405][405][205];

bool valid(int x, int y)
{
    return (0 <= x && x <= 400 && 0 <= y && y <= 400);
}

ll func(int x, int y, int t)
{
    if (!valid(x, y))
        return 0;

    if (dp[x][y][t] != -1)
        return dp[x][y][t];

    if (x == x2 && y == y2)
        return dp[x][y][t] = 1;

    if (t == 0)
        return 0;

    ll ret = 0;
    for (int i = 0; i < 4; i++)
    {
        int X = x + dx[i], Y = y + dy[i];
        if (!board[X][Y])
            ret += func(X, Y, t - 1);
    }

    return dp[x][y][t] = (ret % MOD);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    cin >> _x1 >> _y1 >> t >> x2 >> y2;

    int dx = 200 - _x1, dy = 200 - _y1;
    _x1 += dx, x2 += dx, _y1 += dy, y2 += dy;

    int m;
    cin >> m;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x += dx, y += dy;
        if (valid(x, y))
            board[x][y] = 1;
    }

    cout << func(_x1, _y1, t);
}