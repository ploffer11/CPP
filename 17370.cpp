#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

const pii UP = {0, 1};
const pii DOWN = {0, -1};
const pii RIGHT_UP = {1, 1};
const pii RIGHT_DOWN = {1, -1};
const pii LEFT_UP = {-1, 1};
const pii LEFT_DOWN = {-1, -1};

int n, board[100][100], visit[100][100];
int ans;

map<pii, int> conv;
pii d[][2] = {
    {LEFT_UP, RIGHT_UP},
    {LEFT_DOWN, RIGHT_DOWN},
    {UP, RIGHT_DOWN},
    {DOWN, RIGHT_UP},
    {UP, LEFT_DOWN},
    {DOWN, LEFT_UP},
};
/* 

UP -> 0
DOWN -> 1
RIGHT UP -> 2
RIGHT DOWN -> 3
LEFT UP -> 4
LEFT DOWN -> 5

*/

void back_tracking(int depth, int dir, int x, int y)
{
    if (depth == n)
        return;

    visit[x][y] = true;
    for (int i = 0; i < 2; i++)
    {
        auto [dx, dy] = d[dir][i];
        int X = x + dx, Y = y + dy;

        ans += (visit[X][Y] && depth + 1 == n);

        if (!visit[X][Y])
        {
            back_tracking(depth + 1, conv[{dx, dy}], X, Y);
        }
    }
    visit[x][y] = false;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    conv[UP] = 0;
    conv[DOWN] = 1;
    conv[RIGHT_UP] = 2;
    conv[RIGHT_DOWN] = 3;
    conv[LEFT_UP] = 4;
    conv[LEFT_DOWN] = 5;

    cin >> n;

    visit[50][50] = true;
    back_tracking(0, 0, 50, 51);
    cout << ans;
}