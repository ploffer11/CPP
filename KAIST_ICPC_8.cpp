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

class FenwickTree
{
private:
    int n;
    vector<ll> tree;

    ll _query(int idx)
    {
        ll ret = 0;
        while (idx)
        {
            ret += tree[idx];
            idx -= (-idx & idx);
        }
        return ret;
    }

public:
    FenwickTree(int n) : n(n)
    {
        tree.resize(n + 10, 0);
    }

    void update(int idx, ll diff)
    {
        while (idx <= n)
        {
            tree[idx] += diff;
            idx += (-idx & idx);
        }
    }

    ll query(int l, int r)
    {
        return _query(r) - _query(l - 1);
    }
};

int n;
vector<pii> a;
vector<int> b;
int idx[250'005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    FenwickTree Tree(n);

    b.resize(n);

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a.push_back({x, i + 1});
        Tree.update(i + 1, 1);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        idx[n + 1 - b[i]] = i;
    }

    sort(a.begin(), a.end(), [&](pii &a, pii &b) { return idx[a.first] < idx[b.first]; });
    reverse(a.begin(), a.end());

    ll ans = 0;     
    for (auto [x, y] : a)
    {
        cout << x << " " << y << " " << Tree.query(y + 1, n) << "\n";
        ans += Tree.query(y + 1, n);
        Tree.update(y, -1);
    }

    cout << ans;
}