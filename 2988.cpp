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

pii arr[300'005];
int inp[4][300'005];
int cnt[4][300'005];
bool del[300'005];
int ans;
void f(int i, int j)
{
    if (cnt[i][j] == 0 && !del[j])
    {
        //cout << j << " -> ";
        ans++;
        del[j] = true;
        auto [x, y] = arr[j];
        cnt[2][x]--;
        cnt[3][y]--;

        f(2, x);
        f(3, y);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int j = 1; j <= 3; j++)
        for (int i = 1; i <= n; i++)
            cin >> inp[j][i];

    for (int i = 1; i <= n; i++)
        arr[inp[1][i]] = {inp[2][i], inp[3][i]};

    for (int i = 1; i <= n; i++)
    {
        auto [x, y] = arr[i];
        cnt[2][x]++;
        cnt[3][y]++;
    }

    for (int j = 2; j <= 3; j++)
        for (int i = 1; i <= n; i++)
            f(j, i);

    cout << ans;
}