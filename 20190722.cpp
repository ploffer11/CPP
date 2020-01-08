#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 98765432123456789;
const int MOD = 1e9 + 7;

int n, m, k;
int arr[300005], cnt[300005];
ll sum, ans, dp[300005], constant[300005];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
        constant[i] = (ll)k * ceil((double)i / m);
    }

    for (int i = 1; i <= n; i++)
    {
        if (dp[i - 1] + arr[i] < 0)
        {
            dp[i] = 0;
            cnt[i] = 0;
        }
        else if (dp[i] + arr[i] >=)
            dp[i]   
    }
}