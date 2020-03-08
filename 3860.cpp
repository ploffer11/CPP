#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int NOTHING = 0;
const int RIP = 1;
const int GHOST = 2;

bool visit[1005];
int cycle[1005], inq[1005];
ll dis[1005];

int n, m;
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
int board[35][35];
vector<pll> adj[1005];

bool check(int r, int c)
{
    return (0 <= r && r < n && 0 <= c && c < m);
}

int f(int r, int c)
{
    return m * r + c;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    while (1)
    {
        for (int i = 0; i <= 1000; i++)
            adj[i].clear();

        memset(board, 0, sizeof(board));
        memset(dis, 0x3f, sizeof(dis));
        memset(visit, 0, sizeof(visit));
        memset(cycle, 0, sizeof(cycle));
        memset(inq, 0, sizeof(inq));

        cin >> m >> n;

        const int OFFSET = m * n + 5;

        if (n + m == 0)
            return 0;

        int e, g;

        cin >> g;
        while (g--)
        {
            int a, b;
            cin >> a >> b;
            board[b][a] = RIP;
        }
        cin >> e;
        while (e--)
        {
            int a, b, c, d, e;
            cin >> a >> b >> c >> d >> e;
            board[b][a] = GHOST;

            adj[f(b, a)].push_back({f(d, c), e});
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == n - 1 && j == m - 1)
                    continue;
                if (board[i][j] == NOTHING) //&& i != n - 1 && j != m - 1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int R = i + dr[k], C = j + dc[k];
                        if (check(R, C) && board[R][C] != RIP)
                        {
                            adj[f(i, j)].push_back({f(R, C), 1});
                        }
                    }
                }
            }
        }

        queue<int> q;
        q.push(f(0, 0));
        dis[f(0, 0)] = 0;
        inq[f(0, 0)] = true;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inq[s] = false;

            if (cycle[s] >= OFFSET)
                continue;

            for (auto [e, cost] : adj[s])
            {
                if (dis[e] > dis[s] + cost)
                {
                    dis[e] = dis[s] + cost;
                    if (!inq[e])
                    {
                        cycle[e]++;
                        q.push(e);
                        inq[e] = true;
                    }
                }
            }
        }

        bool cycle_flag = false;
        for (int i = f(0, 0); i <= f(n - 1, m - 1); i++)
        {
            if (cycle[i] >= OFFSET)
            {
                cycle_flag = true;
            }
        }
        if (cycle_flag)
            cout << "Never\n";
        else if (dis[f(n - 1, m - 1)] >= INF)
            cout << "Impossible\n";
        else
            cout << dis[f(n - 1, m - 1)] << "\n";
    }
}
