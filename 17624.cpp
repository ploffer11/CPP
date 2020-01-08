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
const int MAX = 5005;

int n, b, q, cnt;
vector<int> adj[MAX];
bool check[MAX][MAX];
int black[MAX], visit[MAX];
int parent[MAX], sz[MAX], dp[MAX], udp[MAX], usz[MAX], idx[MAX];
int S[MAX], E[MAX];

void dfs1(int s)
{
    visit[s] = true;
    S[s] = ++cnt;
    idx[cnt] = s;

    int &x = sz[s];
    int &y = dp[s];

    for (auto e : adj[s])
    {
        if (!visit[e])
        {
            parent[e] = s;
            dfs1(e);
            x += sz[e];
            y += dp[e];
        }
    }

    x += 1;
    y += black[s];
    E[s] = cnt;
}

void dfs2(int s, int sz_sum, int dp_sum)
{
    usz[s] = sz_sum;
    udp[s] = dp_sum;

    int new_sz_sum = sz_sum + 1, new_dp_sum = dp_sum + black[s];

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            new_sz_sum += sz[e];
            new_dp_sum += dp[e];
        }
    }

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            dfs2(e, new_sz_sum - sz[e], new_dp_sum - dp[e]);
        }
    }
}

vector<pii> dfs3(int s, int child)
{
    vector<pii> ret;
    for (auto e : adj[s])
    {
        if (e == child)
            continue;
        if (e == parent[s])
        {
            for (auto i : dfs3(e, s))
                ret.push_back(i);
            ret.push_back({usz[s], udp[s]});
        }
        if (s == parent[e])
        {
            for (int i = S[e]; i <= E[e]; i++)
            {
                ret.push_back({sz[idx[i]], dp[idx[i]]});
            }
        }
    }
    return ret;
}

void fill_check(int s)
{
    cout << "fill_check: " << s << " -> " << usz[s] << " " << udp[s] << "\n";
    check[usz[s]][udp[s]] = true;
    for (auto [x, y] : dfs3(parent[s], s))
    {
        cout << "x, y: " << x << " " << y << "\n";
        check[usz[s] - x][udp[s] - y] = true;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> b;

    while (b--)
    {
        int x;
        cin >> x;
        black[x] = true;
    }

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1);
    dfs2(1, 0, 0);

    for (int i = 1; i <= n; i++)
    {
        cout << i << ": " << sz[i] << " " << dp[i] << "\n";
    }

    cout << "---------------------------------------------------\n";
    for (int i = 2; i <= n; i++)
    {
        cout << i << ": " << usz[i] << " " << udp[i] << "\n";
    }

    for (int i = 1; i <= n; i++)
    {
        int x = sz[i], y = dp[i];
        check[x][y] = true;
        for (int j = S[i] + 1; j <= E[i]; j++)
        {
            check[x - sz[idx[j]]][y - dp[idx[j]]] = true;
        }
    }

    for (int i = 2; i <= n; i++)
        fill_check(i);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cout << check[i][j] << (j == n ? "\n" : " ");

    int ans = 0;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        ans += check[x][y];
    }
    cout << ans;
}