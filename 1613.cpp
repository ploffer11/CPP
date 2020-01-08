#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n, k, s;
int dis[405][405];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k;

    while (k--)
    {
        int a, b;
        cin >> a >> b;
        dis[a][b] = 1;
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] |= (dis[i][k] & dis[k][j]);

    cin >> s;

    while (s--)
    { 
        int a, b;
        cin >> a >> b;

        if (dis[a][b])
            cout << "-1\n";

        else if (dis[b][a])
            cout << "1\n";

        else
            cout << "0\n";
    }
}