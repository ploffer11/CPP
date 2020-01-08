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
const int MAX = 1000005;

struct KMP
{
    vector<int> fail;
    vector<int> ans;

    void make_fail(string &p)
    {
        int i = 0, j = 0, n = p.size();
        fail.resize(p.size(), 0);
        while (++i < n)
        {
            while (j && p[i] != p[j])
                j = fail[j - 1];
            if (p[i] == p[j])
                fail[i] = ++j;
        }
    }

    void kmp(string &s, string &p)
    {
        int n = s.size(), m = p.size();
        make_fail(p);

        int ret = 0, i = 0, j = 0;

        while (i < n)
        {
            while (j && s[i] != p[j])
                j = fail[j - 1];

            if (s[i] == p[j])
            {
                if (j == m - 1)
                {
                    ans.push_back(i - m + 2);
                    j = fail[j];
                }
                else
                    j++;
            }
            i++;
        }
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    string s, p;
    getline(cin, s);
    getline(cin, p);

    kmp(s, p);

    cout << ans.size() << "\n";
    for (auto i : ans)
        cout << i << " ";
}