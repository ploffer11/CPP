#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
// #define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

vector<pair<int, ll>> adj[4001];
class SPFA
{
private:
    int n;
    vector<bool> inq;
    vector<ll> dis;

public:
    SPFA(int n) : dis(n + 1), inq(n + 1), n(n) {}

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);

        deque<int> q;
        dis[s] = 0;
        q.push_back(s);
        inq[s] = true;

        while (!q.empty())
        {
            int s = q.front();
            q.pop_front();
            inq[s] = false;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    if (!inq[e])
                    {
                        q.push_back(e);
                        inq[e] = true;
                        if (dis[q.back()] < dis[q.front()])
                        {
                            q.push_front(q.back());
                            q.pop_back();
                        }
                        
                    }
                }
            }
        }
        return dis[e];
    }
    
    ll query(int e)
    {
        return dis[e];
    }
};

int arr[2001][201], rsum[2001][201], csum[2001][201];

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int r, c;
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> arr[i][j];
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            rsum[i][j] = rsum[i][j - 1] + arr[i][j];
            csum[i][j] = csum[i - 1][j] + arr[i][j];
        }
    }
    
    auto get_rsum = [&](int r, int cl, int cr) {
        return (cl <= cr ? rsum[r][cr] - rsum[r][cl - 1] : 0LL);
    };
    
    vector<SPFA> graph(2 * r + 1, SPFA(2 * r));
    vector<tuple<int, int, int>> edge;
    for (int i = 1; i <= r; i++)
    {
        int left_node = i, right_node = r + i;
        edge.push_back({left_node, right_node, get_rsum(i, 2, c)});
        edge.push_back({right_node, left_node, get_rsum(i, 1, c - 1)});
        if (i == r)
            break;
        edge.push_back({left_node, left_node + 1, arr[i + 1][1]});
        edge.push_back({left_node + 1, left_node, arr[i][1]});
        edge.push_back({right_node, right_node + 1, arr[i + 1][c]});
        edge.push_back({right_node + 1, right_node, arr[i][c]});
    }
    
    for (auto [u, v, w] : edge)
        adj[u].push_back({v, w});
    
    for (int i = 1; i <= 2 * r; i++)
        graph[i].query(i, i);
    
    auto query = [&](int r1, int c1, int r2, int c2) {
        int _1 = r1, _2 = r2, _3 = r + r1, _4 = r + r2;
        
        ll temp = 0x3f3f3f3f3f3f3f3f;
        if (r1 == r2)
            temp = (c1 < c2 ? get_rsum(r1, c1 + 1, c2) : get_rsum(r1, c2, c1 - 1));
        
        return min({
            temp,
            get_rsum(r1, 1, c1 - 1) + graph[_1].query(_2) + get_rsum(r2, 2, c2),
            get_rsum(r1, 1, c1 - 1) + graph[_1].query(_4) + get_rsum(r2, c2, c - 1),
            get_rsum(r1, c1 + 1, c) + graph[_3].query(_2) + get_rsum(r2, 2, c2),
            get_rsum(r1, c1 + 1, c) + graph[_3].query(_4) + get_rsum(r2, c2, c - 1)
        });
    };
    
    ll ans = arr[1][1];
    int prev_r = 1, prev_c = 1;
    int q;
    cin >> q;
    while (q--)
    {
        int R, C;
        cin >> R >> C;
        ans += query(prev_r, prev_c, R, C);
        prev_r = R, prev_c = C;
    }
    
    cout << ans << endl;
}