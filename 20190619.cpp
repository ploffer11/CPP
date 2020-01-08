#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int, int> tt;

int board[2005][2005];
int board2[2005][2005];

void init(int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            board[i][j] = board2[i][j] = '.';
        }
    }
}
int main()
{
    for (int i = 0; i <= 2000; i++)
    {
        for (int j = 0; j <= 2000; j++)
        {
            board2[i][j] = '.';
        }
    }

    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int r, c;
        cin >> r >> c;

        map<int, vector<pll>> valid;
        for (int i = 0; i < r; i++)
        {
            string x;
            cin >> x;
            for (int j = 0; j < c; j++)
            {
                board[i][j] = (char)x[j];
                if (board[i][j] != '.')
                {
                    valid[board[i][j] - 'a'].push_back(pll(i, j));
                }
            }
        }

        bool flag = false;
        for (int i = 0; i < 26; i++)
        {

            if (valid[i].size() == 0 || valid[i].size() == 1)
            {
                continue;
            }
            else if (valid[i][0].first == valid[i][1].first)
            {
                for (auto j : valid[i])
                {
                    if (j.first != valid[i][0].first)
                    {
                        flag = true;

                        cout << "NO\n";
                        break;
                    }
                }
            }

            else if (valid[i][0].second == valid[i][1].second)
            {
                for (auto j : valid[i])
                {
                    if (j.second != valid[i][0].second)
                    {
                        flag = true;
                        cout << "NO\n";
                        break;
                    }
                }
            }

            else
            {
                flag = true;
                cout << "NO\n";
            }

            if (flag)
                break;
        }
        if (flag)
        {
            init(r, c);
            continue;
        }

        vector<tt> ans;
        ans.resize(26, tt(-1, -1, -1, -1));
        int ans2 = -1;
        for (int i = 0; i < 26; i++)
        {
            if (valid[i].size() == 0)
            {
                continue;
            }
            else if (valid[i].size() == 1)
            {
                auto [x, y] = valid[i][0];
                board2[x][y] = 'a' + i;
                ans[i] = tt(x, y, x, y);
            }

            else if (valid[i][0].first == valid[i][1].first)
            {
                int R = valid[i][0].first, Cmin = 9999999, Cmax = -1;
                for (auto [x, y] : valid[i])
                {
                    Cmin = min(Cmin, (int)y);
                    Cmax = max(Cmax, (int)y);
                }

                for (int j = Cmin; j <= Cmax; j++)
                {
                    board2[R][j] = 'a' + i;
                }
                ans[i] = tt(R, Cmin, R, Cmax);
            }

            else if (valid[i][0].second == valid[i][1].second)
            {
                int C = valid[i][0].second, Rmin = 9999999, Rmax = -1;
                for (auto [x, y] : valid[i])
                {
                    Rmin = min(Rmin, (int)x);
                    Rmax = max(Rmax, (int)x);
                }

                for (int j = Rmin; j <= Rmax; j++)
                {
                    board2[j][C] = 'a' + i;
                }

                ans[i] = tt(Rmin, C, Rmax, C);
            }

            ans2 = max(ans2, i);
        }

        bool flag2 = false;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (board[i][j] != board2[i][j])
                {
                    flag2 = true;
                    break;
                }
            }
            if (flag2)
                break;
        }

        init(r, c);
        if (flag2)
        {
            cout << "NO\n";
            continue;
        }
        else
        {
            cout << "YES\n";
            cout << ans2 + 1 << '\n';
            for (int i = 0; i <= ans2; i++)
            {
                auto [a, b, c, d] = ans[i];

                if (a == -1)
                {
                    auto [_1, _2, _3, _4] = ans[ans2];
                    cout << _1 + 1 << " " << _2 + 1 << " " << _3 + 1 << " " << _4 + 1 << "\n";
                }
                else
                {

                    cout << a + 1 << " " << b + 1 << " " << c + 1 << " " << d + 1 << "\n";
                }
            }
        }
    }
}