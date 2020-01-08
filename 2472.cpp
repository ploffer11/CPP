#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;
const int MAX = 100'005;

int n;
bool finish[MAX], ans[MAX];
ll dis[MAX][3];
vector<pii> adj[MAX];

class SegmentTree
{
private:
    vector<ll> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, INF);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = min(tree[i], diff);
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

void dijkstra(int s, int m)
{
    for (int i = 1; i <= n; i++)
        dis[i][m] = INF;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    dis[s][m] = 0;

    while (!pq.empty())
    {
        auto [cur, s] = pq.top();
        pq.pop();

        if (finish[s])
            continue;

        for (auto [e, cost] : adj[s])
        {
            if (dis[e][m] > cur + cost)
            {
                dis[e][m] = cur + cost;
                pq.push({dis[e][m], e});
            }
        }

        finish[s] = true;
    }

    memset(finish, 0, sizeof(finish));
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    SegmentTree Tree(n);

    int a, b, c;
    cin >> a >> b >> c;

    int m;
    cin >> m;
    dijkstra(a, 0);
    dijkstra(b, 1);
    dijkstra(c, 2);

    vector<tuple<int, int, int, int>> t;
    vector<int> cp;
    for (int i = 1; i <= n; i++)
    {
        t.push_back({dis[i][0], dis[i][1], dis[i][2], i});
        cp.push_back(dis[i][1]);
    }

    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());

    sort(t.begin(), t.end());

    for (auto [x, y, z, i] : t)
    {
        int k = (lower_bound(cp.begin(), cp.end(), y) - cp.begin()) + 1;

        ll Z = (k == 1 ? INF : Tree.query(1, 1, n, 1, k - 1));

        if (Z >= z)
            ans[i] = true;
        else
            ans[i] = false;

        Tree.update_idx(1, 1, n, k, z);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int x;
        cin >> x;
        cout << (ans[x] ? "YES\n" : "NO\n");
    }
}