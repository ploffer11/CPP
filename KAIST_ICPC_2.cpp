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

ll f(vector<pii> &vt)
{
    int t = 0;
    ll ret = 0;
    for (auto [x, y] : vt)
    {
        t += x;
        ret += (t + 20 * y);
    }
    return ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<pii> vt;
    for (int i = 1; i <= 11; i++)
    {
        int x, y;
        cin >> x >> y;
        vt.push_back({x, y});
    }
    sort(vt.begin(), vt.end());

    ll ans = INF;
    do
    {
        ans = min(ans, f(vt));

    } while (next_permutation(vt.begin(), vt.end()));

    cout << ans;
}