#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

ll arr[1000005], n;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<tuple<int, int, int>> ans;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    int i = n;
    while (i >= 1)
    {
        int e = i;
        ll s = arr[i], len = 1;
        while (i >= 2 && s * (len + 1) <= (s + arr[i - 1]) * len)
        {
            len++;
            s += arr[i - 1];
            i--;
        }
        ans.push_back({i--, e, s});
    }

    for (int i = ans.size() - 1; i >= 0; i--)
    {
        auto [s, e, x] = ans[i];
        for (int j = 0; j < e - s + 1; j++)
        {
            printf("%.20lf\n", (double)x / (e - s + 1));
        }
    }
}