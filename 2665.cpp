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

int n, dis[55][55], visit[55][55];
char arr[55][55];
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
bool valid(int r, int c)
{
    return (1 <= r && r <= n && 1 <= c && c <= n);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dis, 0x3f, sizeof(dis));

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arr[i][j];

    using tt = tuple<int, int, int>;
    priority_queue<tt, vector<tt>, greater<tt>> pq;
    pq.push({0, 1, 1});
    dis[1][1] = 0;

    while (!pq.empty())
    {
        auto [cur, r, c] = pq.top();
        pq.pop();

        if (visit[r][c])
            continue;

        for (int i = 0; i < 4; i++)
        {
            int R = r + dr[i], C = c + dc[i];
            int weight = (arr[R][C] == '0');
            if (valid(R, C) && dis[R][C] > dis[r][c] + weight)
            {
                dis[R][C] = dis[r][c] + weight;
                pq.push({dis[R][C], R, C});
            }
        }

        visit[r][c] = true;
    }

    cout << dis[n][n];
}