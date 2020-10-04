#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
// #define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 2e9;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 200001;

#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin() + 1; };

ll ans;
vector<pair<int, int>> adj[MAX];
int V[MAX], C[MAX];
int s_idx[MAX];

set<pair<ll, int>> S[MAX];

void dfs(int i, ll cur)
{
    for (auto [j, w] : adj[i])
    {
        dfs(j, cur + w);
        if (S[s_idx[i]].size() < S[s_idx[j]].size())
            swap(s_idx[i], s_idx[j]);
        
        for (auto k : S[s_idx[j]])
            S[s_idx[i]].insert(k);
        S[s_idx[j]].clear();       
    }
    
    if (V[i] < 0)
    {
        S[s_idx[i]].insert({cur, i});
        return;
    }
    
    int cnt = 0;
    auto &s = S[s_idx[i]];
    while (C[i] > 0 && !s.empty())
    {
        cnt++;
        auto iter = s.upper_bound(pair<ll, int>(cur + V[i], INF));
        
        // 전부다 나보다 큼
        if (iter == s.begin())
            break;
        else 
            iter--;
        
        auto [depth, j] = *iter;
        ll temp = min(C[i], C[j]);
        C[j] -= temp;
        C[i] -= temp;
        ans += temp;
        if (C[j] == 0)
            s.erase(pair<ll, int>(depth, j));
    }
}

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++)
        cin >> C[i];
    
    for (int i = 1; i <= n; i++)
    {
        cin >> V[i];
        s_idx[i] = i;
    }
    
    vector<pii> edge(n + 1);
    for (int i = 2; i <= n; i++)
        cin >> edge[i].first;
    for (int i = 2; i <= n; i++)
        cin >> edge[i].second;
    for (int i = 2; i <= n; i++)
        adj[edge[i].first].push_back({i, edge[i].second});
    
    dfs(1, 0LL);
    
    cout << ans << "\n";
}