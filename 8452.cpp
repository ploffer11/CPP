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
const int MAX = 1001;

#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin(); };

int dis[MAX][MAX];
bool del[MAX];

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n, m, q;
    cin >> n >> m >> q;
    
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        dis[u][v] = 1;
    }
    
    vector<pair<char, int>> query;
    for (int i = 1, y; i <= q; i++)
    {
        char x;
        cin >> x >> y;
        query.push_back({x, y});
        FUCK
        //if (x == 'U')
        
        
    }
    
}