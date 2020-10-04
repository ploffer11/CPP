#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin(); };

int D[5001][5001];
vector<int> near;
vector<pair<int, ll>> adj[5001];

class SPFA
{
private:
    int n;
    vector<bool> inq;
    vector<int> cycle, dis;

public:
    SPFA(int n) : dis(n + 1), inq(n + 1), n(n) {}

    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    int query(int x)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f);
        
        deque<int> q;
        dis[1] = 0;
        q.push_back(1);
        inq[1] = true;
        
        double sum = 0;
        while (!q.empty())
        {
            int s = q.front();
            q.pop_front();
            inq[s] = false;
            sum -= dis[s];

            for (auto [e, w] : adj[s])
            {
                if (s == x && e == 1 || s == 1 && e == x)
                    continue;
                    
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    if (!inq[e])
                    {
                        q.push_back(e);
                        sum += dis[e];
                        inq[e] = true;
                        while (sum / q.size() < dis[q.front()])
                        {
                            q.push_back(q.front());
                            q.pop_front();
                        }
                    }
                }
            }
        }
        
        return dis[x];
    }
    
};

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    
    SPFA graph(n);
    
    
    while (m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        
        graph.add_edge(a, b, c);
        graph.add_edge(b, a, d);
        D[a][b] = c;
        D[b][a] = d;
        
        if (a == 1)
            near.push_back(b);
        else if (b == 1)
            near.push_back(a);
    }
    
    int ans = INF;
    for (auto i : near)
    {
        ans = min(ans, graph.query(i) + D[i][1]);
    }
    cout << ans;
    
    
    
    
    
}