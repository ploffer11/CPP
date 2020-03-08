#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

int go[][5] = {
    {1, 2, 3, 4, 5},
    {2, 3, 4, 5, 6},
    {3, 4, 5, 6, 7},
    {4, 5, 6, 7, 8},
    {5, 6, 7, 8, 9},
    {22, 23, 24, 25, 31}, // 5
    {7, 8, 9, 10, 11},
    {8, 9, 10, 11, 12},
    {9, 10, 11, 12, 13},
    {10, 11, 12, 13, 14},
    {26, 27, 25, 31, 32}, // 10
    {12, 13, 14, 15, 16},
    {13, 14, 15, 16, 17},
    {14, 15, 16, 17, 18},
    {15, 16, 17, 18, 19},
    {28, 29, 30, 25, 31}, // 15
    {17, 18, 19, 20, 21},
    {18, 19, 20, 21, 21},
    {19, 20, 21, 21, 21},
    {20, 21, 21, 21, 21},
    {21, 21, 21, 21, 21}, // 20
    {21, 21, 21, 21, 21},
    {23, 24, 25, 31, 32},
    {24, 25, 31, 32, 20},
    {25, 31, 32, 20, 21},
    {31, 32, 20, 21, 21}, // 25
    {27, 25, 31, 32, 20},
    {25, 31, 32, 20, 21},
    {29, 30, 25, 31, 32},
    {30, 25, 31, 32, 20}, //29
    {25, 31, 32, 20, 21},
    {32, 20, 21, 21, 21},
    {20, 21, 21, 21, 21} // 32
};

int score[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
    32, 34, 36, 38, 40, 0, 13, 16, 19, 25, 22, 24, 28, 27, 26, 30, 35};

struct board
{
    vector<int> pos;
    int total, depth;

    board(vector<int> pos, int total, int depth) : pos(pos), total(total), depth(depth)
    {
    }

    board()
    {
        pos = {0, 0, 0, 0};
        total = 0;
        depth = 0;
    }

    board next_state(int idx, int walk)
    {
        vector<int> copy_pos = pos;
        int &idx_pos = copy_pos[idx];
        int ini_pos = copy_pos[idx];

        int go_pos = go[ini_pos][walk - 1];

        if (go_pos == 21)
        {
            idx_pos = 21;
        }
        else
        {
            bool flag = false;
            for (int j = 0; j < 4; j++)
                if (pos[j] == go_pos)
                    flag = true;

            if (!flag)
                idx_pos = go_pos;
        }

        if (ini_pos == idx_pos)
            return board(copy_pos, 0, 10);

        return board(copy_pos, total + score[idx_pos], depth + 1);
    }
};

int ans;
int dice[10];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    for (int i = 0; i < 10; i++)
        cin >> dice[i];

    queue<board> q;
    q.push(board());

    while (!q.empty())
    {
        board cur = q.front();
        q.pop();
        ans = max(ans, cur.total);

        if (cur.depth == 10)
            continue;

        for (int i = 0; i < 4; i++)
        {
            q.push(cur.next_state(i, dice[cur.depth]));
        }
    }

    cout << ans;
}