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
const int MAX = 100'005;

int arr[MAX], dp[MAX], can[MAX], ans[MAX];
int N, S;

int sum(int l, int r)
{
    if (l <= 0 || r > N)
        return 200'000'000'5;
    return dp[r] - dp[l - 1];
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> N >> S;

    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        dp[i] = dp[i - 1] + arr[i];
    }

    for (int i = 1; i <= N; i++)
    {
        int s = 1, e = N;

        while (s <= e)
        {
            int m = (s + e) >> 1;
            int x = sum(i - m + 1, i);
            int y = sum(i + 1, i + m);

            if (x > S || y > S)
                e = m - 1;
            else
                s = m + 1;
        }

        ans[i - e + 1] = max(ans[i - e + 1], e);
    }

    int y = -1;
    for (int i = 1; i <= N; i++)
    {
        cout << max(y * 2, ans[i] * 2) << "\n";
        y = max(--y, ans[i] - 1);
    }
}