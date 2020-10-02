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

class MaxSegmentTree
{
private:
    vector<ll> tree;

public:
    MaxSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) >> 1;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    ll n, m;
    cin >> n >> m;
    vector<int> lock, cp;
    vector<tuple<ll, ll, ll, ll>> vt;
    
    for (ll i = 0, x, y, v, h; i < n; i++)
    {
        cin >> x >> y >> v >> h;
        lock.push_back(h);
        cp.push_back(y);
        vt.push_back({x, y, v, h});
    }
    
    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());
    auto f = [&](int x) {
        return lower_bound(cp.begin(), cp.end(), x) - cp.begin() + 1;   
    };

    for (auto &[_1, _2, _3, _4] : vt)
        _2 = f(_2);
    
    sort(vt.begin(), vt.end());

    sort(lock.begin(), lock.end());
    lock.resize(unique(lock.begin(), lock.end()) - lock.begin());
    
    int l = 0, r = 0;
    ll ans = INF;
    MaxSegmentTree tree(n);
    while (l < lock.size() && r < lock.size())
    {
        vector<int> upd;
        ll mx = -INF;
        for (auto [x, y, v, h] : vt)
        {
            if (lock[l] <= h && h <= lock[r])
            {
                ll q = tree.query(1, 1, n, 1, y);
                tree.update_idx(1, 1, n, y, q + v);
                mx = max(mx, q + v);
                upd.push_back(y);
            }
        }
        for (auto y : upd)
            tree.update_idx(1, 1, n, y, 0);
        if (mx >= m)
            ans = min(ans, lock[r] - lock[l]), l++;
        else 
            r++;
    }
    cout << (ans == INF ? -1 : ans);
}