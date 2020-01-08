#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int board[1005][1005], near_ice[1005][1005], number[1005][1005], parent[1000010];
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
pii ans = {-1, -1};

map<int, int> mp;

int find(int me)
{
    if (parent[me] < 0)
        return me;
    else
        return parent[me] = find(parent[me]);
}

void uni(int a, int b)
{
    a = find(a), b = find(b);
    if (a != b)
    {
        parent[a] += parent[b];
        parent[b] = a;
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        string inp;
        cin >> inp;
        for (int j = 1; j <= n; j++)
        {
            number[i][j] = n * (i - 1) + j;
            if (inp[j - 1] == '#')
                board[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (board[i][j])
            {
                int cnt = 0;
                for (int k = 0; k < 4; k++)
                {
                    int R = i + dr[k], C = j + dc[k];
                    if (board[R][C])
                    {
                        cnt++;
                        uni(number[i][j], number[R][C]);
                    }
                }
                near_ice[i][j] = cnt;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            mp[find(number[i][j])] += 4 - near_ice[i][j];
        }
    }

    for (auto [me, area] : mp)
    {
        ans = max(ans, pii(-parent[me], -area));
    }

    auto [area, perimeter] = ans;
    cout << area << " " << -perimeter;
}