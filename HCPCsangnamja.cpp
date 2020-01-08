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

int arr[400005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= 4 * n; i++)
        arr[i % k]++;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        arr[x % k]--;
        arr[y % k]--;
    }
    int a, b;
    cin >> a >> b;
    arr[a % k]--;
    arr[b % k]--;
    int score = abs(a % k - b % k);

    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = i + score + 1; j < k; j++)
        {
            int x = min(arr[i], arr[j]);
            arr[i] -= x;
            arr[j] -= x;
            ans += x;
            if (x)
                cout << i << " <-> " << j << "\n";
        }
        if (ans >= m - 1)
            break;
    }
    cout << min(ans, m - 1);
}