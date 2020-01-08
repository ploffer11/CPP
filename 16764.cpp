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

map<vector<int>, ll> mp;
vector<int> ice[50005];
vector<int> idx;
vector<int> temp;
ll ans, n;

void f(int depth, int max_depth, int i, int num)
{
    if (depth == max_depth)
    {
        //cout << depth << " " << k << " " << i << " " << num << "\n";
        mp[temp]++;
        return;
    }

    for (int j = i; j < 5; j++)
    {
        temp.push_back(ice[num][j]);
        f(depth + 1, max_depth, j + 1, num);
        temp.pop_back();
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int x;
        for (int j = 1; j <= 5; j++)
        {
            cin >> x;
            ice[i].push_back(x);
        }
        sort(ice[i].begin(), ice[i].end());
    }

    ll ans = (n * (n - 1)) / 2;
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= 5; k++)
            f(0, k, 0, i);

    for (auto &[i, j] : mp)
        if (j >= 2)
            ans += (i.size() % 2 == 0 ? 1 : -1) * ((j * (j - 1)) / 2);

    cout << ans;
}