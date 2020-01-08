//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f;
const int MOD = 1e9 + 7;
const int MAX = 5001;

int n, b, q, cnt, s1, s2, e1, e2;

bool visit[MAX];
vector<short> adj[MAX];
short black[MAX], S[MAX], E[MAX];
short M[MAX][MAX], X[MAX][MAX];
short temp[MAX], temp2[MAX];
short last[MAX];

void dfs(int i)
{
    visit[i] = true;
    M[i][black[i]] = 1;
    X[i][black[i]] = 1;
    last[i] = black[i];

    for (auto e : adj[i])
    {
        if (!visit[e])
        {
            dfs(e);

            s1 = black[i];
            e1 = last[i];

            s2 = black[e];
            e2 = last[e];

            for (int j = s2; j <= e2; j++)
            {
                for (int k = e1 + j; s1 <= k - j; k--)
                {
                    temp[k] = min(temp[k], min(M[i][k], (short)(M[i][k - j] + M[e][j])));
                    temp2[k] = max(temp2[k], max(X[i][k], (short)(X[i][k - j] + X[e][j])));
                }
            }

            for (int j = 0; j <= b; j++)
            {
                if (temp[j] != INF)
                    last[i] = j;

                M[i][j] = min(temp[j], M[i][j]);
                X[i][j] = max(temp2[j], X[i][j]);
                temp[j] = INF;
                temp2[j] = 0;
            }
        }
    }
}

char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}

int readInt()
{
    int ret = 0, flg = 1;
    char now = read();

    while (isspace(now))
        now = read();
    if (now == '-')
        flg = -1, now = read();
    while (now >= 48 && now <= 57)
    {
        ret = ret * 10 + now - 48;
        now = read();
    }
    return ret * flg;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    memset(M, 0x3f, sizeof(M));
    memset(S, 0x3f, sizeof(S));
    memset(temp, 0x3f, sizeof(temp));
    memset(last, -1, sizeof(last));

    n = readInt();
    b = readInt();

    for (int i = 1; i <= b; i++)
        black[readInt()] = true;

    for (int i = 1; i <= n - 1; i++)
    {
        int u = readInt(), v = readInt();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= b; j++)
        {
            S[j] = min(S[j], M[i][j]);
            E[j] = max(E[j], X[i][j]);
        }
    }

    int ans = 0;
    q = readInt();
    while (q--)
    {
        int x = readInt(), y = readInt();
        ans += (S[y] <= x && x <= E[y]);
    }
    cout << ans;
}