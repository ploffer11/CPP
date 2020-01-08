#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 100'005;

ll x;
ll delta = 0;
int n;
int A[MAX], B[MAX];
int dp_A[MAX], dp_B[MAX];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> A[i];
    for (int i = 1; i <= n; i++)
        cin >> B[i];

    delta = -n;
    for (int i = n; i >= 1; i--)
    {
        delta += A[i];
        delta += B[i];
        dp_A[i] = dp_A[i + 1] + (A[i] == 0);
        dp_B[i] = dp_B[i + 1] + (B[i] == 0);
    }

    for (int i = 1; i <= n; i++)
    {
        if (A[i] == 1)
            x += dp_A[i + 1];
        if (B[i] == 1)
            x -= dp_B[i + 1];
    }

    ll ans = abs(x);

    // [rightmost 1] [leftmost 0]
    ll temp = x;
    ll total = 0;
    int i = n, j = 1;
    while (1)
    {
        while (A[i] == 0 && i >= 1)
            i--;
        while (B[j] == 1 && j <= n)
            j++;

        if (!(i >= 1 && j <= n))
            break;

        //cout << i << " " << j << " <- 1\n";

        ll y = -(n - i) + (j - 1);
        ll demand = (n - i--) + (j++ - 1);

        temp += y;
        total += demand;
        ans = min(ans, abs(temp) + total);

        temp += delta;
        total++;
        ans = min(ans, abs(temp) + total);
    }

    // [rightmost 0] [leftmost 1]

    temp = x;
    total = 0;
    i = n, j = 1;
    while (1)
    {
        while (A[i] == 1 && i >= 1)
            i--;
        while (B[j] == 0 && j <= n)
            j++;

        //cout << i << " " << j << " <- 2\n";
        if (!(i >= 1 && j <= n))
            break;

        ll y = (n - i) - (j - 1);
        ll demand = (n - i--) + (j++ - 1);

        temp += y;
        total += demand;
        ans = min(ans, abs(temp) + total);

        temp -= delta;
        total++;
        ans = min(ans, abs(temp) + total);
    }

    cout << ans;
}