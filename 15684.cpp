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

int C, X, R, ans = 4;
vector<vector<int>> sadari;
vector<pii> can;

int f(int idx)
{
    int cur = idx;
    for (int j = 0; j < R; j++)
    {
        int x = -1, y = -1;
        if (cur != 0)
            x = sadari[j][cur - 1];
        if (cur != C - 1)
            y = sadari[j][cur];
        if (x == 1)
            cur--;
        if (y == 1)
            cur++;
    }
    return cur;
}

bool valid()
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C - 2; j++)
            if (sadari[i][j] == 1 && sadari[i][j + 1] == 1)
                return false;
    return true;
}

int cnt = 0;
void check(int depth, int max_depth, int idx)
{
    if (ans <= max_depth)
        return;

    if (depth == max_depth)
    {
        if (!valid())
            return;
        bool flag = true;
        for (int i = 0; i < C; i++)
        {
            if (f(i) != i)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            ans = min(ans, max_depth);
        return;
    }
    for (int i = idx + 1; i < can.size(); i++)
    {
        auto [r, c] = can[i];

        sadari[r][c] = 1;
        check(depth + 1, max_depth, i);
        sadari[r][c] = 0;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> C >> X >> R;

    sadari.resize(R, vector<int>(C - 1, 0));

    for (int i = 0; i < X; i++)
    {
        int c, r;
        cin >> r >> c;
        sadari[r - 1][c - 1] = 1;
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C - 1; j++)
        {
            bool flag = true;
            if (sadari[i][j] == 0)
            {
                if (j != 0 && sadari[i][j - 1])
                    flag = false;
                if (j != C - 2 && sadari[i][j + 1])
                    flag = false;
                if (flag)
                    can.push_back({i, j});
            }
        }
    }

    check(0, 0, -1);
    if (can.size() >= 1)
        check(0, 1, -1);

    if (can.size() >= 2)
        check(0, 2, -1);

    if (can.size() >= 3)
        check(0, 3, -1);

    cout << (ans == 4 ? -1 : ans);
}