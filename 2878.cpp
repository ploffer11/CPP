#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

ll m, n;
vector<ll> want;

bool check(ll x)
{
    ll total = m;
    for (auto i : want)
    {
        ll give = i - x;
        if (give <= 0)
            continue;
        else if (give > total)
            return false;
        else
            total -= give;
    }
    return true;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> m >> n;
    want.resize(n);

    for (int i = 0; i < n; i++)
        cin >> want[i];

    ll s = 0, e = (ll)1 << 33;
    while (s <= e)
    {
        ll m = (s + e) >> 1;

        if (check(m))
            e = m - 1;
        else
            s = m + 1;
    }

    ll total = m;
    for (auto &i : want)
    {
        ll give = i - s;

        if (give <= 0)
            continue;

        total -= i - s;
        i = s;
    }

    using ull = unsigned long long;
    priority_queue<ull, vector<ull>, less<ull>> pq;

    for (auto i : want)
        pq.push(i);

    while (total > 0)
    {
        pq.push(pq.top() - 1);
        pq.pop();
        total--;
    }

    ull ans = 0;
    while (!pq.empty())
    {
        ull x = pq.top();
        ans += x * x;
        pq.pop();
    }

    cout << ans;
}