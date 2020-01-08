#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 1'000'000;

int n, m;
int number[1005][1005], price[1005][1005];
int dis[MAX];
bool in_queue[MAX];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> price[i][j];
            number[i][j] = (i - 1) * n + j;
        }
    }

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j<=m; j++)
        {
            
        }
    }
}