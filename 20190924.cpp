#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ll gcd(ll a, ll b)
{
    if (a == 0 || b == 0)
        return (a == 0 ? b : a);

    return (a % b == 0 ? b : gcd(b, a % b));
}

vector<int> adj[100005];
ll x[100005];
bool visit[100005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll ans = x[1];

    using mp = map<ll, int>;
    queue<pair<int, mp>> q;
    mp temp;
    temp[x[1]] = 1;
    visit[1] = true;

    q.push({1, temp});
    while (!q.empty())
    {
        auto [node, m] = q.front();
        q.pop();

        for (auto e : adj[node])
        {
            if (!visit[e])
            {
                temp.clear();
                visit[e] = true;
                temp[x[e]] = 1;
                ans = (ans + x[e]) % MOD;
                for (auto [g, cnt] : m)
                {
                    ll y = gcd(g, x[e]);
                    temp[y] += cnt;
                    y %= MOD;
                    ans = (ans + y * cnt) % MOD;
                }
                q.push({e, temp});
            }
        }
    }

    cout << ans % MOD;
}