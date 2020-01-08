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

int prefix[400005], suffix[400005];
int cnt[400005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= 4 * n; i++)
        cnt[i % k]++;

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        cnt[a % k]--;
        cnt[b % k]--;
    }
    int x, y;
    cin >> x >> y;
    cnt[x % k]--;
    cnt[y % k]--;
    for (int i = 0; i < m; i++)
        cout << cnt[i] << " ";
    cout << "\n";
    int score = abs(x % k - y % k);

    prefix[0] = cnt[0];
    for (int i = 1; i < k; i++)
        prefix[i] = prefix[i - 1] + cnt[i];

    suffix[k - 1] = cnt[k - 1];
    for (int i = k - 2; i >= 0; i--)
        suffix[i] = suffix[i + 1] + cnt[i];

    cout << "score: " << score << "\n";
    //   3점   0~3  7~9  9까지존재
    int ans = 0;
    for (int i = 0; i + score + 1 < k; i++)
    {
        cout << prefix[i] << " " << suffix[i + score + 1] << "\n";
        ans = max(ans, min(prefix[i], suffix[i + score + 1]));
    }

    cout << min(ans, m - 1);
}