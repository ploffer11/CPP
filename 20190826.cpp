#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int arr[2005], dp[2005][2005];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x3f, sizeof(dp));

    int n;
    cin >> n;

    set<int> st;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        st.insert(arr[i]);
    }
    if (st.size() == n)
    {
        cout << 0;
        return 0;
    }

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        if (arr[i] == arr[i + 1])
            dp[i][i + 1] = 1;
        else
            dp[i][i + 1] = 0;
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j + i <= n; j++)
        {
            bool flag = false;
            for (int k = j + 1; k <= j + i; k++)
                if (arr[k] == arr[j])
                    flag = true;
            dp[j][j + i] = min(dp[j][j + i], dp[j + 1][j + i] + flag);

            flag = false;
            for (int k = j; k <= i + j - 1; k++)
                if (arr[k] == arr[i + j])
                    flag = true;
            dp[j][j + i] = min(dp[j][j + i], dp[j][j + i - 1] + flag);
        }
    }

    cout << dp[1][n];
}
