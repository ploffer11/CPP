#include <bits/stdc++.h>
using namespace std;

int board[505][505];
int dr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
int dc[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
vector<pair<int, int>> ans;

void bomb(int r, int c, int k)
{
    int cnt = 0;
    for (int i = 0; i < 9; i++)
        cnt += board[r + dr[i]][c + dc[i]];

    if (cnt == k)
    {
        for (int i = 0; i < 9; i++)
            board[r + dr[i]][c + dc[i]] = 0;

        ans.push_back({r, c});
    }
}

int main()
{
    setbuf(stdout, NULL);
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        int r, c;
        cin >> r >> c;

        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                scanf("%1d", &board[i][j]);
            }
        }

        for (int k = 9; k >= 1; k--)
        {
            for (int i = 1; i <= r - 2; i++)
            {
                for (int j = 1; j <= c - 2; j++)
                {
                    bomb(i, j, k);
                }
            }
        }
        cout << "Case #" << t << '\n';
        cout << ans.size() << '\n';
        for (auto &i : ans)
        {
            cout << i.first << " " << i.second << '\n';
        }

        fflush(stdout);

        ans.clear();
    }
}