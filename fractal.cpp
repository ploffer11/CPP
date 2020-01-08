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

int board[1100][1100];

int dstate[][4] = {
    {0, 1, 7, 4},
    {1, 2, 4, 5},
    {2, 3, 5, 6},
    {3, 6, 0, 7},
    {4, 7, 6, 0},
    {5, 4, 1, 2},
    {6, 5, 3, 2},
    {7, 6, 0, 1},
};

// 0 -> 0, 1 -> 0, 2 -> 1, 3 -> 1
int dr[][4] = {
    {0, 0, 1, 1},
    {1, 0, 0, 1},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 1},
};

// 1, 3 -> 1
int dc[][4] = {
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1},
    {1, 1, 0, 0},
    {1, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
};

int dr2[][4] = {
    {0, 0, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 0},
    {1, 0, 1, 0},
};

// 1, 3 -> 1
int dc2[][4] = {
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 0},
};

void func(int state, int r, int c, int k, int sum, int save)
{
    //cout << state << " " << r << " " << c << " -> ";
    int k2 = k / 2;
    int square = (sum) / (k2 * k2);

    if (k == 2)
    {
        //cout << r << " " << c << "\n";
        board[r + dr2[state][sum]][c + dc2[state][sum]] = save;
        return;
    }

    func(dstate[state][square], r + k2 * dr[state][square], c + k2 * dc[state][square], k2, sum - square * k2 * k2, save);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int k = 16;
    for (int i = 0; i < k * k; i++)
    {
        func(0, 0, 0, k, i, i);
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout.width(3);
            cout << board[i][j] << (j == k - 1 ? "\n" : " ");
        }
    }
}