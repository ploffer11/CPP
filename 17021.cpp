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
const int MAX = 5005;

ll dp[MAX], rhyme[MAX], ans[MAX];
int cnt[MAX][MAX], cnt2[MAX];
int line[30];

ll power(int a, int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return a;

    ll b = power(a, n / 2);
    return (n % 2 == 1 ? (((b * b) % MOD) * a) % MOD : ((b * b) % MOD));
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        int length, rhyme_class;
        cin >> length >> rhyme_class;
        cnt[rhyme_class][length]++;
        cnt2[length]++;
    }

    for (int i = 1; i <= m; i++)
    {
        char x;
        cin >> x;
        line[x - 'A']++;
    }

    dp[0] = 1;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; i - j >= 0 && j <= k; j++)
        {
            dp[i] += dp[i - j] * cnt2[j];
            dp[i] %= MOD;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; k - j >= 0 && j <= k; j++)
        {
            rhyme[i] += dp[k - j] * cnt[i][j];
            rhyme[i] %= MOD;
        }
        //cout << i << " --> " << rhyme[i] << "\n";
    }

    for (int i = 0; i < 26; i++)
    {
        if (line[i] == 0)
            continue;

        for (int j = 1; j <= n; j++)
        {
            if (rhyme[j] == 0)
                continue;
            ans[i] += power(rhyme[j], line[i]);
            ans[i] %= MOD;
        }
    }

    ll answer = 1;
    bool flag = true;

    for (int i = 0; i < 26; i++)
    {
        if (ans[i] != 0)
            flag = false;

        //cout << ans[i] << " ";
        answer *= (ans[i] == 0 ? 1 : ans[i]);
        answer %= MOD;
    }

    cout << (flag ? 0 : answer);
}