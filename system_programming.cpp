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

static int x = 15;
int f()
{
    static int x = 17;
    return x++;
}
int g()
{
    static int x = 19;
    return x += 14;
}
int h()
{
    return x += 100;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout << f() << " " << g() << " " << h() << "\n";
}