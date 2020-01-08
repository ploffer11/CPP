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

class MOs
{
private:
    const int SQRT = 400;
    pii prev = {1, 0};
    vector<pii> query;
    vector<tuple<int, int, int>> order;
    vector<ll> cnt, qans, arr;
    ll ans = 0;

    void add(int i)
    {
        ll &j = cnt[arr[i]];
        ans += arr[i] * (2LL * j + 1);
        j++;
    }
    void del(int i)
    {
        ll &j = cnt[arr[i]];
        ans += arr[i] * (1 - 2LL * j);
        j--;
    }
    void update_query(pii now)
    {
        auto [l1, r1] = prev;
        auto [l2, r2] = now;
        for (int i = l1 - 1; i >= l2; i--)
            add(i);
        for (int i = r1 + 1; i <= r2; i++)
            add(i);
        for (int i = l1; i < l2; i++)
            del(i);
        for (int i = r1; i > r2; i--)
            del(i);
        prev = now;
    }
    void sort_order()
    {
        for (int i = 0; i < query.size(); i++)
        {
            auto [l, r] = query[i];
            order.push_back({l / SQRT, r, i});
        }
        sort(order.begin(), order.end());
    }

public:
    MOs(int n) : cnt(1000005), arr(n + 1), ans(0) {}
    void add_arr(int i, int val)
    {
        arr[i] = val;
    }
    void add_query(int l, int r)
    {
        query.push_back({l, r});
    }
    vector<ll> &get_ans()
    {
        sort_order();
        qans.resize(query.size());
        for (auto [x, y, i] : order)
        {
            update_query(query[i]);
            qans[i] = ans;
        }
        return qans;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    MOs mos(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        mos.add_arr(i, x);
    }

    while (q--)
    {
        int x, y;
        cin >> x >> y;
        mos.add_query(x, y);
    }

    for (auto i : mos.get_ans())
        cout << i << "\n";
}