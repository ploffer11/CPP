#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, e;
    cin >> n >> e;

    vector<pii> vt;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        vt.push_back({a, b});
    }

    sort(vt.begin(), vt.end());

    int ans = 1;
    pii range = {vt[0].second - e, vt[0].second + e};

    for (int i = 1; i < vt.size(); i++)
    {
        auto [a, b] = vt[i];
        auto [d, u] = range;
        auto down = b - e, up = b + e;

        if (down <= d && u <= up)
            continue;

        else if (d <= down && up <= u)
        {
            range = {down, up};
        }

        else if (d <= down && down <= u && up >= u)
        {
            range = {down, u};
        }

        else if (d <= up && up <= u && down <= d)
        {
            range = {d, up};
        }
        else
        {
            ans++;
            range = {down, up};
        }
    }

    cout << ans;
}