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

bool alp[30][2];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--)
    {
        memset(alp, 0, sizeof(alp));
        string s, t;
        cin >> s >> t;
        for (auto i : s)
            alp[i - 'a'][0] = true;
        for (auto i : t)
            alp[i - 'a'][1] = true;

        bool flag = true;
        for (int i = 0; i < 26; i++)
            if (alp[i][1] && !alp[i][0])
                flag = false;

        if (!flag)
        {
            cout << "-1\n";
            continue;
        }

        vector<vector<int>> vt(26);

        for (int i = 0; i < s.size(); i++)
        {
            vt[s[i] - 'a'].push_back(i);
        }

        int ans = 1;
        int k = 0;
        for (auto i : t)
        {
            auto &x = vt[i - 'a'];
            int idx = lower_bound(x.begin(), x.end(), k) - x.begin();

            if (idx == x.size())
            {
                ans++;
                k = 0;
                idx = lower_bound(x.begin(), x.end(), k) - x.begin();
            }
            k = x[idx] + 1;
        }

        cout << ans << "\n";
    }
}