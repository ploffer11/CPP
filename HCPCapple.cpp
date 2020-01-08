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

int arr[2][10001];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "2\n1\n2";
        return 0;
    }

    arr[0][1] = 2 * n - 1;
    arr[0][n] = 2 * n;

    arr[1][n] = 2 * n - 2;
    arr[1][1] = 2 * n - 3;
    for (int i = 2; i <= n - 1; i++)
    {
        arr[0][i] = n - i;
        arr[1][i] = 2 * n - 2 - i;
    }

    deque<int> a, b;
    for (int i = 1; i <= n; i++)
        a.push_back(arr[0][i]);

    for (int i = 1; i <= n; i++)
        b.push_back(arr[1][i]);

    ll sum = (2 * n * (2 * n + 1)) / 2;
    ll ans = 0;
    ll cnt = 0;
    while (a.size() && b.size())
    {
        pii x = {INF, INF};
        x = min(x, {a.back(), 1});
        x = min(x, {a[0], 2});
        x = min(x, {b.back(), 3});
        x = min(x, {b[0], 4});

        switch (x.second)
        {
        case 1:
            a.pop_back();
            break;
        case 2:
            a.pop_front();
            break;
        case 3:
            b.pop_back();
            break;
        case 4:
            b.pop_front();
            break;
        }
        sum -= x.first;
        ans += sum * (++cnt);
    }

    if (b.size())
        swap(a, b);

    while (a.size())
    {
        pii x = {INF, INF};
        x = min(x, {a.back(), 1});
        x = min(x, {a[0], 2});

        switch (x.second)
        {
        case 1:
            a.pop_back();
            break;
        case 2:
            a.pop_front();
            break;
        }
        sum -= x.first;
        ans += sum * (++cnt);
    }

    cout << ans << "\n";
    for (int j = 0; j <= 1; j++)
        for (int i = 1; i <= n; i++)
            cout << arr[j][i] << (i == n ? "\n" : " ");
}