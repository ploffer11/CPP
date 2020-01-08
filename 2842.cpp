#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int post_r, post_c;
char board[52][52];
int number[52][52], height[52][52], visit[52][52];
int dr[] = {1, 1, 1, 0, 0, -1, -1, -1};
int dc[] = {1, 0, -1, 1, -1, 1, 0, -1};
vector<pii> delivery;
vector<int> save;

int n;
int parent[2505];

bool check(int r, int c)
{
    return (1 <= r && r <= n && 1 <= c && c <= n);
}

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

int parametric_search(int s_height)
{
    if (height[post_r][post_c] < s_height)
        return INF;

    for (auto [r, c] : delivery)
        if (height[r][c] < s_height)
            return INF;

    int s = 0, e = 100'0005;
    while (s <= e)
    {
        memset(parent, -1, sizeof(parent));
        int m = (s + e) / 2;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (!(s_height <= height[i][j] && height[i][j] <= s_height + m))
                    continue;
                for (int k = 0; k < 8; k++)
                {
                    int R = i + dr[k], C = j + dc[k];
                    if (check(R, C) && (s_height <= height[R][C] && height[R][C] <= s_height + m))
                        uni(number[i][j], number[R][C]);
                }
            }
        }

        bool flag = true;
        for (auto [r, c] : delivery)
        {
            if (find(number[post_r][post_c]) != find(number[r][c]))
            {
                flag = false;
                break;
            }
        }

        if (flag)
            e = m - 1;
        else
            s = m + 1;
    }

    //cout << s_height << " " << s << " <-> " << e << '\n';
    return s;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    for (int i = 1; i <= 50; i++)
    {
        for (int j = 1; j <= 50; j++)
        {
            number[i][j] = (i - 1) * 50 + j;
        }
    }

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 'K')
                delivery.push_back({i, j});
            else if (board[i][j] == 'P')
                post_r = i, post_c = j;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> height[i][j];
            save.push_back(height[i][j]);
        }
    }

    sort(save.begin(), save.end());
    save.resize(unique(save.begin(), save.end()) - save.begin());

    int ans = INF;
    for (auto i : save)
    {
        ans = min(ans, parametric_search(i));
    }
    cout << ans;
}