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

vector<pii> score[505];
vector<pii> path[505];
int d[505][505], dis[505][505], S[505][505];
int s[505][505], e[505][505];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int x;
            cin >> x;
            score[i].push_back({(x == 0 ? INF : x), j});
        }
    }

    for (int i = 1; i <= n; i++)
    {
        sort(score[i].begin(), score[i].end());
        for (int j = 0; j < score[i].size(); j++)
        {
            auto [q, w] = score[i][j];
            for (int k = j + 1; k < score[i].size(); k++)
            {
                auto [e, r] = score[i][k];
                if (q == e)
                    continue;
                d[w][r]++;
            }
        }
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            cout << d[i][j] << (j == m ? "\n" : " ");

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            if (d[i][j] > d[j][i])
                dis[i][j] = 1;

    for (int k = 1; k <= m; k++)
    {
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= m; j++)
            {
            }
        }
    }
}