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
const int PILLAR = 0, BO = 1;

bool bo[105][105], pillar[105][105];

vector<vector<int>> solution(int n, vector<vector<int>> build_frame)
{
    vector<vector<int>> ans;

    for (auto &i : build_frame)
    {
        int x = i[0], y = i[1], a = i[2], b = i[3];

        if (a == PILLAR)
        {
            if (b)
            {
                if (y == 0 || pillar[x][y - 1] || bo[x][y] || bo[x - 1][y])
                {
                    pillar[x][y] = true;
                }
            }
            else
            {
                if (!bo[x][y + 1] || (bo[x - 1][y + 1] && bo[x][y + 1]))
                    pillar[x][y] = false;
            }
        }

        else if (a == BO)
        {
            if (b)
            {
                if (pillar[x][y - 1] || pillar[x + 1][y - 1] || (bo[x - 1][y] && bo[x + 1][y]))
                {
                    bo[x][y] = true;
                }
            }
            else
            {
                bool cond1 = pillar[x][y - 1] && pillar[x + 1][y - 1];
                bool cond2 = (pillar[x][y - 1] && (!bo[x + 1][y] || (pillar[x + 1][y - 1] || pillar[x + 2][y - 1])));
                bool cond3 = (pillar[x + 1][y - 1] && (!bo[x - 1][y] || (pillar[x - 1][y - 1] || pillar[x][y - 1])));

                if (cond1 || cond2 || cond3)
                    bo[x][y] = false;
            }
        }
    }

    for (int i = 0; i <= 100; i++)
    {
        for (int j = 0; j <= 100; j++)
        {
            if (bo[i][j])
            {
                vector<int> vt = {i, j, BO};
                ans.push_back(vt);
            }
            if (pillar[i][j])
            {
                vector<int> vt = {i, j, PILLAR};
                ans.push_back(vt);
            }
        }
    }

    return ans;
}