#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("O3")
// #pragma GCC optimize ("unroll-loops")
// #define int long long
using namespace std;
using ll = int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 2e9 + 10000;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

int dis[4001][4001];
bool inq[4001];
vector<pair<int, ll>> adj[4001];

class SPFA
{
public:
    SPFA(int n) {}

    ll query(int s, int e)
    {
        queue<int> q;
        q.push(s);
        dis[s][s] = 0;
        inq[s] = true;
        while (!q.empty())
        {
            int S = q.front();
            q.pop();
            inq[S] = false;

            for (auto [e, w] : adj[S])
            {
                if (dis[s][e] > dis[s][S] + w)
                {
                    dis[s][e] = dis[s][S] + w;
                    if (!inq[e])
                    {
                        q.push(e);
                        inq[e] = true;
                    }
                }
            }
        }
        return dis[s][e];
    }
};

int r, c;
vector<SPFA> graph(2 * 2000 + 1, SPFA(2 * 2000));
int arr[2001][201], rsum[2001][201];

inline int get_rsum(int r, int cl, int cr) 
{
    return (cl <= cr ? rsum[r][cr] - rsum[r][cl - 1] : 0);
}

inline void add_edge(int s, int e, int x)
{
    adj[s].push_back({e, x});
}

inline int query(int r1, int c1, int r2, int c2) 
{
    int _1 = r1, _2 = r2, _3 = r + r1, _4 = r + r2;
    
    int temp = 2e9 + 10000;
    if (r1 == r2)
        temp = (c1 < c2 ? get_rsum(r1, c1 + 1, c2) : get_rsum(r1, c2, c1 - 1));
    
    return min({
        temp,
        get_rsum(r1, 1, c1 - 1) + dis[_1][_2] + get_rsum(r2, 2, c2),
        get_rsum(r1, 1, c1 - 1) + dis[_1][_4] + get_rsum(r2, c2, c - 1),
        get_rsum(r1, c1 + 1, c) + dis[_3][_2] + get_rsum(r2, 2, c2),
        get_rsum(r1, c1 + 1, c) + dis[_3][_4] + get_rsum(r2, c2, c - 1)
    });
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
    cin.sync_with_stdio(0);
    
    for (int i = 1; i <= 4000; i++)
        for (int j = 1; j <= 4000; j++)
            dis[i][j] = 2e9 + 10;
    
    r = readInt(), c = readInt();
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            arr[i][j] = readInt(), rsum[i][j] = rsum[i][j - 1] + arr[i][j];
    
    for (int i = 1; i <= r; i++)
    {
        int left_node = i, right_node = r + i;
        add_edge(left_node, right_node, get_rsum(i, 2, c));
        add_edge(right_node, left_node, get_rsum(i, 1, c - 1));
        if (i == r)
            break;
        add_edge(left_node, left_node + 1, arr[i + 1][1]);
        add_edge(left_node + 1, left_node, arr[i][1]);
        add_edge(right_node, right_node + 1, arr[i + 1][c]);
        add_edge(right_node + 1, right_node, arr[i][c]);
    }

    for (int i = 1; i <= 2 * r; i++)
        graph[i].query(i, i);

    long long int ans = arr[1][1];
    int prev_r = 1, prev_c = 1;
    int q = readInt();
    while (q--)
    {
        int R, C;
        R = readInt(), C = readInt();
        ans += query(prev_r, prev_c, R, C);
        prev_r = R, prev_c = C;
    }
    
    cout << ans << endl;
}