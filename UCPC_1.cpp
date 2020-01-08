#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int INF = -1;
const int MOD = 1e9 + 7;

map<string, int> cnt[305];
ll dp[200'005];
string str;

ll f(int n)
{
    if (dp[n] != -1)
        return dp[n];

    ll ret = 0;
    string s = "";
    for (int j = 1; n - j >= 0 && j <= INF; j++)
    {
        s = str[n - j] + s;

        if (dp[n - j] != 0 && cnt[j].find(s) != cnt[j].end())
            ret += f(n - j) * cnt[j][s];

        if (ret >= MOD)
            ret %= MOD;
    }

    return dp[n] = ret;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;

    while (n--)
    {
        string inp;
        cin >> inp;
        for (int i = 1; i <= inp.size(); i++)
        {
            cnt[i][inp.substr(0, i)]++;
        }
        INF = max(INF, (int)inp.size());
    }

    cin >> str;

    dp[0] = 1;
    cout << f(str.size());
}