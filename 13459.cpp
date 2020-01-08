#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int _dr[] = {1, -1, 0, 0};
int _dc[] = {0, 0, 1, -1};

struct Board
{
    vector<vector<char>> board;
    int depth, n, m;
    int r1, c1, r2, c2;
    bool red, blue;

    Board(int n, int m) : n(n), m(m), red(0), blue(0)
    {
        board.resize(n, vector<char>(m, 0));
    }

    bool check(int r, int c)
    {
        return (0 <= r && r < n && 0 <= c && c < m);
    }

    Board *next(int p)
    {
        Board *ptr;
        ptr = new Board(n, m);
        ptr->depth = this->depth + 1;

        vector<vector<char>> ret = board;
        int r1 = this->r1, c1 = this->c1, r2 = this->r2, c2 = this->c2;
        bool red = false, blue = false;

        int dr = _dr[p], dc = _dc[p];

        bool flag = true;

        while (1)
        {
            if (check(r1 + dr, c1 + dc) && (ret[r1 + dr][c1 + dc] == '.'))
            {
                swap(ret[r1][c1], ret[r1 + dr][c1 + dc]);
                r1 += dr;
                c1 += dc;
                flag = false;
            }

            else if (check(r1 + dr, c1 + dc) && ret[r1 + dr][c1 + dc] == 'O')
            {
                ret[r1][c1] = '.';
                red = true;
                flag = false;
                break;
            }

            else
                break;
        }

        while (1)
        {
            if (check(r2 + dr, c2 + dc) && (ret[r2 + dr][c2 + dc] == '.'))
            {
                swap(ret[r2 + dr][c2 + dc], ret[r2][c2]);
                r2 += dr;
                c2 += dc;
                flag = false;
            }

            else if (check(r2 + dr, c2 + dc) && ret[r2 + dr][c2 + dc] == 'O')
            {
                ret[r2][c2] = '.';
                return NULL;
            }

            else
                break;
        }

        while (1)
        {
            if (check(r1 + dr, c1 + dc) && (ret[r1 + dr][c1 + dc] == '.'))
            {
                swap(ret[r1][c1], ret[r1 + dr][c1 + dc]);
                r1 += dr;
                c1 += dc;
                flag = false;
            }

            else if (check(r1 + dr, c1 + dc) && ret[r1 + dr][c1 + dc] == 'O')
            {
                ret[r1][c1] = '.';
                red = true;
                flag = false;
                break;
            }

            else
                break;
        }

        while (1)
        {
            if (check(r2 + dr, c2 + dc) && (ret[r2 + dr][c2 + dc] == '.'))
            {
                swap(ret[r2 + dr][c2 + dc], ret[r2][c2]);
                r2 += dr;
                c2 += dc;
                flag = false;
            }

            else if (check(r2 + dr, c2 + dc) && ret[r2 + dr][c2 + dc] == 'O')
            {
                ret[r2][c2] = '.';
                return NULL;
            }

            else
                break;
        }

        if (flag)
            return NULL;

        ptr->red = red;
        ptr->blue = blue;
        ptr->board = ret;
        ptr->r1 = r1;
        ptr->r2 = r2;
        ptr->c1 = c1;
        ptr->c2 = c2;

        //ptr->debug();
        return ptr;
    }

    void debug()
    {
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    Board InitialBoard(n, m);
    InitialBoard.depth = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> InitialBoard.board[i][j];
            if (InitialBoard.board[i][j] == 'R')
                InitialBoard.r1 = i, InitialBoard.c1 = j;
            else if (InitialBoard.board[i][j] == 'B')
                InitialBoard.r2 = i, InitialBoard.c2 = j;
        }
    }

    queue<Board> q;
    q.push(InitialBoard);

    while (!q.empty())
    {
        auto board = q.front();
        q.pop();

        //cout << board.depth << " " << board.blue << " " << board.blue << endl;
        if (board.depth <= 10 && !board.blue && board.red)
        {
            cout << "1";
            return 0;
        }

        else if (board.depth > 10)
            break;

        else if (board.blue)
            continue;

        for (int i = 0; i < 4; i++)
        {
            auto ret = board.next(i);
            if (ret)
                q.push(*ret);
        }
    }

    cout << "0";
}
