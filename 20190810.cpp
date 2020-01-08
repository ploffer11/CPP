#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int getdiv(ll n)
{
    int ret = 0;
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0)
            ret += (i * i == n ? 1 : 2);
    return ret;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    ll cnt = 0;
    for (ll i = 1; i <= 1000'0000; i++)
    {
        cnt += getdiv(i);
        if (i % 10000 == 0)
        {
            cout << cnt << (i % 100000 == 0 ? ",\n" : ", ");
            cnt = 0;
        }
    }
    cout << "the end";
}