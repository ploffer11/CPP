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

lass MOs
{
private:
    const int SQRT = 400;
    pii prev = {0, 0};
    vector<pii> query;
    vector<tuple<int, int, int>> order;
    vector<int> cnt, qans, arr;
    int ans = 0;

    void add(int i)
    {
        ans += (cnt[arr[i]]++ == 0);
    }

    void del(int i)
    {
        ans -= (--cnt[arr[i]] == 0);
    }

    // [0, 0] -> [2, 5]
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

        qans.resize(query.size());
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

    vector<int> &get_ans()
    {
        sort_order();
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
}