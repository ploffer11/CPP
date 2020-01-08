#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tt = tuple<int, int, int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int GARO = 0, SERO = 1;

int dr[] = {0, 0, 2, -1};
int dc[] = {2, -1, 0, 0};
int dr2[] = {0, 0, 1, -1};
int dc2[] = {1, -1, 0, 0};

vector<vector<int>> board;
int visit[105][105][2];
int n;

bool valid(int r, int c)
{
    return (0 <= r && r < n && 0 <= c && c < n);
}

bool check(int r, int c)
{
    if (!(0 <= r && r + 1 < n && 0 <= c && c + 1 < n))
        return false;

    return (!board[r][c] && !board[r + 1][c] && !board[r][c + 1] && !board[r + 1][c + 1]);
}

void add(queue<tuple<int, int, int, int>> &q, int depth, int r, int c, int dir)
{
    if (!visit[r][c][dir])
    {
        visit[r][c][dir] = depth + 1;
        q.push(tt(depth + 1, r, c, dir));
    }
}

int solution(vector<vector<int>> b)
{
    n = b.size();
    board = b;

    queue<tuple<int, int, int, int>> q;
    visit[0][0][GARO] = 1;
    q.push(tt(1, 0, 0, GARO));

    while (!q.empty())
    {
        auto [depth, r, c, dir] = q.front();
        q.pop();

        //cout << depth << " " << r << " " << c << " " << (dir == 0 ? "GARO" : "SERO") << "\n";
        int a, b;

        if (dir == GARO)
            a = 0, b = 1;
        else
            a = 2, b = 3;

        for (int k = a; k <= b; k++)
        {
            int r1 = r + dr[k], c1 = c + dc[k];
            int r2 = r + dr2[k], c2 = c + dc2[k];
            if (valid(r1, c1) && !board[r1][c1] && !visit[r2][c2][dir])
            {
                visit[r2][c2][dir] = depth + 1;
                q.push(tt(depth + 1, r2, c2, dir));
            }
        }

        if (dir == GARO)
        {
            if (check(r - 1, c))
            {
                add(q, depth, r - 1, c, GARO);
                add(q, depth, r - 1, c, SERO);
                add(q, depth, r - 1, c + 1, SERO);
            }

            if (check(r, c))
            {
                add(q, depth, r + 1, c, GARO);
                add(q, depth, r, c, SERO);
                add(q, depth, r, c + 1, SERO);
            }
        }

        else
        {
            if (check(r, c - 1))
            {
                add(q, depth, r, c - 1, SERO);
                add(q, depth, r, c - 1, GARO);
                add(q, depth, r + 1, c - 1, GARO);
            }

            if (check(r, c))
            {
                add(q, depth, r, c + 1, SERO);
                add(q, depth, r, c, GARO);
                add(q, depth, r + 1, c, GARO);
            }
        }
    }

    int ans = INF;
    if (visit[n - 1][n - 2][GARO])
        ans = min(ans, visit[n - 1][n - 2][GARO]);
    if (visit[n - 2][n - 1][SERO])
        ans = min(ans, visit[n - 2][n - 1][SERO]);

    return ans - 1;
}

int main()
{
    vector<vector<int>> vt = {
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1},
        {1, 1, 0, 0, 1},
        {0, 0, 0, 0, 0}};
    cout << solution(vt);
}
