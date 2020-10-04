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
int depth[100000];
vector<int> tree[100000];
vector<int> near;
pair<vector<int>, vector<int>> vt[100];

class Dijkstra
{
private:
    vector<vector<pair<int, ll>>> adj;
    vector<ll> dis;
    vector<int> via;
    vector<bool> finish;

public:
    Dijkstra(int n) : dis(n + 1), finish(n + 1), adj(n + 1) {}
    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    void query(vector<int> &source)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f);
        fill(finish.begin(), finish.end(), false);

        priority_queue<pll, vector<pll>, greater<pll>> pq;
        
        for (auto s : source)
        {
            pq.push({D[1][s], s});
            dis[s] = D[1][s];
        }
        
        while (!pq.empty())
        {
            auto [cur, s] = pq.top();
            pq.pop();

            if (finish[s])
                continue;
            finish[s] = true;

            for (auto [e, w] : adj[s])
            {
                if (e == 1)
                    continue;
                
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    pq.push({dis[e], e});
                }
            }
        }
    }
    
    int query(int e)
    {
        return dis[e];
    }
};

void fill(int i, int s, int e, int x)
{
    depth[i] = x;
    
    for (int j = s; j <= e; j++)
        tree[i].push_back(near[j]);
    
    if (s == e)
        return;
    int m = (s + e) >> 1;
    fill(2 * i, s, m, x + 1);
    fill(2 * i + 1, m + 1, e, x + 1);
}

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    
    Dijkstra graph(n);
    
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
    
    fill(1, 0, near.size() - 1, 1);
    
    for (int i = 2; i <= 99999; i++)
    {
        if (!depth[i])
            break;
        if (i % 2 == 0)
        {
            for (auto j : tree[i])
                vt[depth[i]].first.push_back(j);
        }
        else
        {
            for (auto j : tree[i])
                vt[depth[i]].second.push_back(j);
        }
    }
    
    vector<int> dis(n + 1, INF);
    for (int i = 2; i <= 50; i++)
    {
        auto [L, R] = vt[i];
        if (L.empty() || R.empty())
            break;
        
        graph.query(L);
        for (auto j : R)
            dis[j] = min(dis[j], graph.query(j));
        graph.query(R);
        for (auto j : L)
            dis[j] = min(dis[j], graph.query(j));
    }
       
    int ans = INF;
    for (auto i : near)
        ans = min(ans, dis[i] + D[i][1]);
    cout << ans;
    
    
}