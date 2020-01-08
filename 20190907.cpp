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

int key[200][200][4], loc[200][200];

vector<vector<int>> rotate(vector<vector<int>> k)
{
    int n = k.size();
    vector<vector<int>> vt;
    vt.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            vt[i][j] = k[n - j - 1][i];
        }
    }

    return vt;
}

int match(int r, int c, int n, int m, int k)
{
    int ret = 0;
    for (int i = r; i < r + m; i++)
    {
        for (int j = c; j < c + m; j++)
        {
            if (m <= i && i < m + n && m <= j && j < m + n)
            {
                if (key[i - r][j - c][k] == 1 && loc[i][j] == 0)
                    ret++;
                else if (key[i - r][j - c][k] == 1 && loc[i][j] == 1)
                    return -1;
            }
        }
    }
    return ret;
}

bool solution(vector<vector<int>> k, vector<vector<int>> l)
{
    int m = k.size();
    int n = l.size();
    int cnt = 0;

    for (int i = m; i < m + n; i++)
        for (int j = m; j < m + n; j++)
            loc[i][j] = l[i - m][j - m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (l[i][j] == 0)
                cnt++;

    auto copy = k;
    for (int k = 0; k < 4; k++)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                key[i][j][k] = copy[i][j];

        copy = rotate(copy);
    }

    for (int k = 0; k < 4; k++)
    {
        for (int i = 1; i < n + m; i++)
        {
            for (int j = 1; j < n + m; j++)
            {
                if (match(i, j, n, m, k) == cnt)
                {
                    return true;
                }
            }
        }
    }
    return false;
}