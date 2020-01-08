#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 998244353;

ll ans = 0;

ll mul(ll x, ll y)
{
    return ((x % MOD) * (y % MOD)) % MOD;
}

struct info
{
    int R, B;
    ll x, X, y, Y;

    info &operator+=(const info &a)
    {
        this->R += a.R;
        this->B += a.B;
        this->x += a.x;
        this->X += a.X;
        this->y += a.y;
        this->Y += a.Y;

        this->R %= MOD;
        this->B %= MOD;
        this->x %= MOD;
        this->X %= MOD;
        this->y %= MOD;
        this->Y %= MOD;

        return *this;
    }
};

class Tree
{
private:
    vector<vector<pii>> adj;
    vector<ll> depth, dis, visit;
    bool flag = true;
    int n, k = 20;

    void dfs(int s, ll dist, int d)
    {
        depth[s] = d;
        dis[s] = dist;

        for (auto [e, cost] : adj[s])
        {
            if (!depth[e])
            {
                dfs(e, dist + cost, d + 1);
            }
        }
    }

public:
    vector<int> check_b, check_r;
    Tree(int n)
    {
        this->n = n;
        visit.resize(n + 1);
        adj.resize(n + 1);
        check_b.resize(n + 1);
        check_r.resize(n + 1);
        depth.resize(n + 1, 0);
        dis.resize(n + 1, 0);
    }

    void init()
    {
        if (!flag)
            return;

        flag = false;
        dfs(1, 0, 1);
    }

    void add_edge(int u, int v, int c = 1)
    {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    info dfs(int s)
    {
        visit[s] = true;
        bool leaf = true;

        info sum = {0, 0, 0, 0, 0, 0};
        vector<info> temp;
        for (auto [e, w] : adj[s])
        {
            if (!visit[e])
            {
                leaf = false;
                auto x = dfs(e);
                sum += x;
                temp.push_back(x);
            }
        }

        info m = {0, 0, 0, 0, 0, 0};
        if (check_r[s])
            m += {1, 0, dis[s], dis[s] * dis[s], 0, 0};
        if (check_b[s])
            m += {0, 1, 0, 0, dis[s], dis[s] * dis[s]};

        if (leaf)
            return m;

        for (auto [R, B, x, X, y, Y] : temp)
        {
            ans += mul(R, sum.Y - Y);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
            ans += mul(X, sum.B - B);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
            ans += 4 * mul(mul(mul(dis[s], dis[s]), R), sum.B - B);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
            ans += 2 * mul(x, sum.y - y);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
            ans += -4 * mul(dis[s], (mul(R, sum.y - y) + mul(x, sum.B - B)) % MOD);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
        }

        if (check_b[s])
        {
            ans += sum.X;
            ans %= MOD;
            while (ans < 0)
                ans += MOD;

            ans += mul(sum.R, dis[s] * dis[s]);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;

            ans += -2 * mul(dis[s], sum.x);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
        }

        if (check_r[s])
        {
            ans += sum.Y;
            ans %= MOD;
            while (ans < 0)
                ans += MOD;

            ans += mul(sum.B, dis[s] * dis[s]);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;

            ans += -2 * mul(dis[s], sum.y);
            ans %= MOD;
            while (ans < 0)
                ans += MOD;
        }

        sum += m;
        return sum;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }

    int m;
    cin >> m;
    while (m--)
    {
        int x;
        cin >> x;
        tree.check_r[x] = true;
    }

    int k;
    cin >> k;
    while (k--)
    {
        int x;
        cin >> x;
        tree.check_b[x] = true;
    }

    tree.init();
    auto [a, b, c, d, e, f] = tree.dfs(1);
    //cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";

    cout << ans;
}