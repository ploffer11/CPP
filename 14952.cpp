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
const int WHITE = 1, BLACK = 2;

int board[10][10], goal_x, goal_y;

set<vector<int>> st;

ll ans;

int dx[][3] = {
    {0, 0, 0},

    {-2, -1, 0},
    {-1, 0, 1},
    {0, 1, 2},

    {-2, -1, 0},
    {-1, 0, 1},
    {0, 1, 2},

    {-2, -1, 0},
    {-1, 0, 1},
    {0, 1, 2},
};

int dy[][3] = {
    {0, -1, -2},

    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},

    {2, 1, 0},
    {1, 0, -1},
    {0, -1, -2},

    {-2, -1, 0},
    {-1, 0, 1},
    {0, 1, 2},
};

int dx2[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dy2[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};

bool valid(int x, int y)
{
    return (1 <= x && x <= 4 && 1 <= y && y <= 4);
}
/*
bool finish(int x, int y, int c)
{
    int ret = 0;
    for (int k = 0; k < 9; k++)
    {
        int X = x + dx2[k], Y = y + dy2[k];
        if (valid(X, Y) && board[X][Y] == c)
            ret++;
    }
    return (ret >= 3);
}
*/

bool finish(int x, int y, int c)
{
    for (int i = 0; i < 10; i++)
    {
        bool k = true;
        for (int j = 0; j < 3; j++)
        {
            int X = x + dx[i][j], Y = y + dy[i][j];
            if (valid(X, Y) && board[X][Y] == c)
                continue;
            else
                k = false;
        }
        if (k)
            return true;
    }
    return false;
}

void back_tracking(int depth, int color, int x, int y)
{

    bool f = finish(x, y, WHITE);
    vector<int> vt;
    vt.resize(5, 1);

    for (int j = 4; j >= 1; j--)
        for (int i = 1; i <= 4; i++)
            if (board[i][j])
                vt[i]++;

    if (color == BLACK && goal_x == x && goal_y == y && f)
    {
        vector<int> key;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                key.push_back(board[i + 1][j + 1]);
        st.insert(key);

        return;
    }

    else if (goal_x == x && goal_y == y)
        return;

    else if (color == WHITE && finish(x, y, BLACK))
        return;

    else if (color == BLACK && f)
        return;

    for (int k = 1; k <= 4; k++)
    {
        if (vt[k] > 4)
            continue;

        board[k][vt[k]] = color;
        back_tracking(depth + 1, 3 - color, k, vt[k]);
        board[k][vt[k]] = 0;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int k;
    cin >> k;
    board[k][1] = BLACK;
    cin >> goal_y >> goal_x;

    back_tracking(1, WHITE, k, 1);

    //cout << ans << "\n";
    cout << st.size() << "\n";
}