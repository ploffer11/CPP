#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define pb(x) push_back(x)
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin(); };

class SPFA
{
private:
    int n;
    vector<bool> inq;
    vector<int> cycle, via;
    vector<ll> dis;
    vector<vector<pair<int, ll>>> adj;

public:
    SPFA(int n) : dis(n + 1), inq(n + 1), adj(n + 1), cycle(n + 1), via(n + 1), n(n) {}

    void add_edge(int s, int e, ll cap)
    {
        adj[s].push_back({e, cap});
    }

    ll query(int s, int e)
    {
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
        fill(cycle.begin(), cycle.end(), 0);

        queue<int> q;
        dis[s] = 0;
        q.push(s);
        inq[s] = true;

        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            inq[s] = false;
            cycle[s]++;

            if (cycle[s] == n)
                continue;

            for (auto [e, w] : adj[s])
            {
                if (dis[e] > dis[s] + w)
                {
                    dis[e] = dis[s] + w;
                    via[e] = s;
                    if (!inq[e])
                    {
                        q.push(e);
                        inq[e] = true;
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


int n, b, s, r;
ll dp[5001][5001], arr[5001];
ll psum[5001];
ll sum(int l, int r)
{
    return psum[r] - psum[l - 1];
}

long long C(int i, int j)
{
    return (j - i) * (sum(i, j));
}


// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int i, int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {INF, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp[i - 1][k] + C(k + 1, mid), k});
    }

    dp[i][mid] = best.first;
    int opt = best.second;

    compute(i, l, mid - 1, optl, opt);
    compute(i, mid + 1, r, opt, optr);
}

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    cin >> n >> b >> s >> r;
    
    SPFA S(n), E(n);
    
    while (r--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        S.add_edge(v, u, w);
        E.add_edge(u, v, w);
    }
    
    S.query(b + 1, 1);
    E.query(b + 1, 1);
    
    vector<int> vt;
    for (int i = 1; i <= b; i++)
        vt.pb(S.query(i) + E.query(i));
        
    sort(all(vt));
    for (int i = 1; i <= b; i++)
    {    
        arr[i] = vt[i - 1];
        psum[i] = psum[i - 1] + arr[i];
    }
    
    for (int i = 1; i <= b; i++)
        dp[1][i] = (i - 1) * sum(1, i);
    
    for (int i = 2; i <= s; i++)
        compute(i, i, b, 0, b);

    cout << dp[s][b] << "\n";
}