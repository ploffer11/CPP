#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

#define all(vt) vt.begin(), vt.end()
#define compress(vt) sort(all(vt)); vt.resize(unique(all(vt)) - vt.begin()); 
#define compress_function(vt, func) auto func = [&](ll k){ return lower_bound(all(vt), k) - vt.begin(); };

int parent[500005];
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
    memset(parent, -1, sizeof(parent));
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    vector<int> cp;
    vector<pii> edge;
    
    int n;
    cin >> n;
    for (int i = 0, x, y; i < n; i++)
    {
        cin >> x >> y;
        edge.push_back({x, y});
        cp.push_back(x);
        cp.push_back(y);
    }
    
    compress(cp);
    compress_function(cp, f);
    vector<int> deg(cp.size());
    for (auto &[x, y] : edge)
    {
        x = f(x), y = f(y);
        deg[x]++;
        deg[y]++;
        uni(x, y);
    }
    
    
    vector<int> E(cp.size());
    vector<vector<int>> V(cp.size());
    for (auto [x, y] : edge)
    {
        E[find(x)]++;
        V[find(x)].push_back(x);
        V[find(y)].push_back(y);
    }
    
    for (int i = 0; i < cp.size(); i++)
    {
        auto &vt = V[i];
        compress(vt);
    }
    
    vector<bool> finish(cp.size());
    ll ans = 0;
    for (int i = 0; i < cp.size(); i++)
    {
        int graph = find(i);
        int edge = E[graph];
        int vertex = V[graph].size(); 
        
        if (finish[graph])
            continue;
        finish[graph] = true;
        
        int mx = -1;
        for (auto i : V[graph])
        {
            mx = max(mx, cp[i]);
            ans += (deg[i] - 1) * cp[i];
        }
        
        if (edge == vertex - 1)
            ans += mx;
    }
    
    cout << ans << "\n";
}