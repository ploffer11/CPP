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

int dp[30][30][2100];
char board[30][30];
int n, m;
int ans, cnt, blank;

bool valid(int r, int c)
{
    return (board[r][c] == '.' && board[r + 1][c] == '.' && board[r][c + 1] == '.' && board[r + 1][c + 1] == '.');
}

void fill(int r, int c, char f)
{
    board[r][c] = board[r + 1][c] = board[r][c + 1] = board[r + 1][c + 1] = f;
}

int get_state(int r, int c)
{
    int ret = 0;
    for (int i = c - 1; i <= m; i++)
    {
        ret <<= 1;
        ret |= (board[r - 1][i] == '1');
    }

    for (int i = 1; i <= c - 1; i++)
    {
        ret <<= 1;
        ret |= (board[r][i] == '1');
    }

    return ret;
}

int f(int r, int c, int state)
{
    if (dp[r][c][state] != -1)
        return dp[r][c][state];

    if (r > n)
        return 0;

    int ret = 0;
    int R = r + (c == m), C = (c == m ? 2 : c + 1);
    if (valid(r - 1, c - 1))
    {
        fill(r - 1, c - 1, '1');
        ret = max(ret, f(R, C, get_state(R, C)) + 1);
        fill(r - 1, c - 1, '.');
    }

    ret = max(ret, f(R, C, get_state(R, C)));

    return dp[r][c][state] = ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    cin >> m >> n;
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            cin >> board[i][j], blank += (board[i][j] == '.'), cnt += (board[i][j] == '1');

    int ans = f(2, 2, get_state(2, 2));
    cout << 16 * ans + (blank - 4 * ans) + cnt << "\n";
}