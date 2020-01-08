#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int fail[1000005];
vector<string> str;
string s, w;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string inp;
        cin >> inp;
        str.push_back(inp);
    }

    string ans = str[0];
    for (int i = 1; i < str.size(); i++)
    {
        w = str[i];

        int start_idx = (w.size() < ans.size() ? ans.size() - w.size() : 0);

        for (int i = 1, j = 0; i < w.size(); i++)
        {
            while (j > 0 && w[i] != w[j])
                j = fail[j - 1];
            if (w[i] == w[j])
                fail[i] = ++j;
        }

        int j = 0;
        for (int i = start_idx; i < s.size(); i++)
        {
            while (j > 0 && s[i] != w[j])
                j = fail[j - 1];

            if (ans[i] == w[j])
                j++;
        }
        ans += w.substr(j, INF);

        for (int i = 0; i < w.size(); i++)
            fail[i] = 0;
    }

    cout << ans;
}