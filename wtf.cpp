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

int visit[100005];
int f(int x, int n, int c)
{
    int m = ~0;
    n = n << 3;
    int y = ((1 << 8) + m) << n;
    int z = y ^ m;
    return (x | y) & (z | (c << n));
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
}