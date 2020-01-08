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
const int GARO = 0, SERO = 1;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int board[105][105], visit[105][105][2];
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
        q.push({depth + 1, r, c, dir});
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    queue<tuple<int, int, int, int>> q;
    visit[0][0][GARO] = 1;
    q.push({1, 0, 0, GARO});

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
            int R = r + dr[k], C = c + dc[k];
            if (valid(R, C) && !visit[R][C][dir])
            {
                visit[R][C][dir] = depth + 1;
                q.push({depth + 1, R, C, dir});
            }
        }

        if (dir == GARO)
        {
            if (check(r - 1, c))
            {
                //add(q, depth, r - 1, c, SERO);
                if (!visit[r - 1][c][SERO])
                {
                    visit[r - 1][c][SERO] = depth + 1;
                    q.push({depth + 1, r - 1, c, SERO});
                }

                if (!visit[r - 1][c + 1][SERO])
                {
                    visit[r - 1][c + 1][SERO] = depth + 1;
                    q.push({depth + 1, r - 1, c + 1, SERO});
                }
            }

            if (check(r, c))
            {
                if (!visit[r][c][SERO])
                {
                    visit[r][c][SERO] = depth + 1;
                    q.push({depth + 1, r, c, SERO});
                }

                if (!visit[r][c + 1][SERO])
                {
                    visit[r][c + 1][SERO] = depth + 1;
                    q.push({depth + 1, r, c + 1, SERO});
                }
            }
        }

        else
        {
            if (check(r, c - 1))
            {
                if (!visit[r][c - 1][GARO])
                {
                    visit[r][c - 1][GARO] = depth + 1;
                    q.push({depth + 1, r, c - 1, GARO});
                }

                if (!visit[r + 1][c - 1][GARO])
                {
                    visit[r + 1][c - 1][GARO] = depth + 1;
                    q.push({depth + 1, r + 1, c - 1, GARO});
                }
            }

            if (check(r, c))
            {
                if (!visit[r][c][GARO])
                {
                    visit[r][c][GARO] = depth + 1;
                    q.push({depth + 1, r, c, GARO});
                }

                if (!visit[r + 1][c][GARO])
                {
                    visit[r + 1][c][GARO] = depth + 1;
                    q.push({depth + 1, r + 1, c, GARO});
                }
            }
        }
    }

    int ans = INF;
    if (visit[n - 1][n - 2][GARO])
        ans = min(ans, visit[n - 1][n - 2][GARO]);
    if (visit[n - 2][n - 1][SERO])
        ans = min(ans, visit[n - 2][n - 1][SERO]);

    cout << ans - 1;
}