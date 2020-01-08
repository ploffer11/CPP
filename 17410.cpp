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

int arr[100005];
vector<int> vt[330];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    int sqrt_n = sqrt(n);
    int total = ceil((double)n / sqrt_n);

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        arr[i] = x;
        vt[i / sqrt_n].push_back(x);
    }

    for (int i = 0; i < total; i++)
        sort(vt[i].begin(), vt[i].end());

    int q;
    cin >> q;

    while (q--)
    {
        int a, b, c, d;
        cin >> a >> b >> c;
        if (a == 2)
        {
            cin >> d;
            b--;
            c--;

            int l = ceil((double)b / sqrt_n);
            int r = (c + 1) / sqrt_n;

            int ans = 0;
            for (int i = l; i < r; i++)
            {
                ans += vt[i].size() - (upper_bound(vt[i].begin(), vt[i].end(), d) - vt[i].begin());
            }

            int L = l * sqrt_n, R = r * sqrt_n;

            if (L > R)
            {
                for (int i = b; i <= c; i++)
                    if (arr[i] > d)
                        ans++;
            }
            else
            {
                for (int i = b; i < L; i++)
                    if (arr[i] > d)
                        ans++;

                for (int i = R; i <= c; i++)
                    if (arr[i] > d)
                        ans++;
            }

            cout << ans << "\n";
        }
        else
        {
            b--;
            int j = b / sqrt_n;
            vt[j].erase(lower_bound(vt[j].begin(), vt[j].end(), arr[b]));
            vt[j].insert(lower_bound(vt[j].begin(), vt[j].end(), c), c);
            arr[b] = c;
        }
    }
}