#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;
const int OFFSET = 1000000;

ll dp[5005][5005], cnt[5005][5005];
int arr[5005];
int chk[2000005];

ll f(int i, int j)
{
    if (j - i <= 1)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    return dp[i][j] = cnt[i][j] + f(i + 1, j) + f(i, j - 1) - f(i + 1, j - 1);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        arr[i] = x;
    }

    for (int i = 1; i + 2 <= n; i++)
    {
        chk[arr[i + 1] + OFFSET]++;

        for (int j = i + 2; j <= n; j++)
        {
            int temp = -(arr[i] + arr[j]) + OFFSET;
            if (0 <= temp && temp <= 2000000)
                cnt[i][j] = chk[temp];
            chk[arr[j] + OFFSET]++;
        }

        for (int j = i + 1; j <= n; j++)
            chk[arr[j] + OFFSET]--;
    }

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << f(l, r) << "\n";
    }
}