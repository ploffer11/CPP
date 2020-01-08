#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 770;

int query[1'000'005];
int board[MAX][MAX];
int parent[MAX * MAX + 10000];
pii height[1'000'005];

int dr[] = {0, 0, 1, -1, 0, 1, 1, -1, -1};
int dc[] = {1, -1, 0, 0, 0, 1, -1, 1, -1};

int f(pii x)
{
    return x.first * MAX + x.second;
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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(parent, -1, sizeof(parent));
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            height[x] = {i, j};
        }
    }

    ll ans = 0;

    int cnt = 0;
    for (int i = 1; i <= 1'000'000; i++)
    {
        if (height[i] == pii(0, 0))
            continue;

        auto [r, c] = height[i];

        board[r][c] = 1;
        for (int j = 0; j < 4; j++)
        {
            int R = r + dr[j], C = c + dc[j];
            if (board[R][C])
                uni(f({r, c}), f({R, C}));
        }

        int j = f(height[i]);
        ans += -parent[j];
        query[i] = -parent[j];
    }   

    /*

    memset(parent, -1, sizeof(parent));
    vector<pii> edge;
    queue<pii> q;

    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            if (!(1 <= i && i <= n && 1 <= j && j <= n))
                edge.push_back({i, j});

    for (int i = 1; i < edge.size(); i++)
    {
        uni(f(edge[0]), f(edge[i]));
    }

    for (int h = 1'000'000; h >= 1; h--)
    {
        if (height[h] == pii(0, 0))
            continue;

        auto [r, c] = height[h];

        board[r][c] = 0;
        for (int i = 0; i < 9; i++)
        {
            int R = r + dr[i], C = c + dc[i];
            if (!board[R][C] && !board[r][c])
            {
                uni(f({R, C}), f({r, c}));
            }
        }

        auto &i = height[h];
        if (find(f(i)) != find(f(edge[0])))
            ans -= (query[h] - 1);
    }
    */

    cout << ans;
}