#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
const int INF = 987654321;
const int MOD = 1e9 + 7;

ld calculate(vector<ll> &vt)
{
    vector<ld> x;
    x.push_back(0);
    ld ret = vt[0] + vt.back();

    for (int i = 1; i < vt.size(); i++)
    {
        ld a = vt[i - 1] + vt[i];
        ld b = abs(vt[i - 1] - vt[i]);
        ld c = sqrt(a * a - b * b);
        x.push_back(x.back() + c);
        ret += c;
    }

    for (int i = 0; i < vt.size(); i++)
    {
        for (int j = i + 1; j < vt.size(); j++)
        {
            ld a = x[i] - x[i - 1];
            ld b = abs(vt[i - 1] - vt[i]);
            ld c = vt[i - 1] + vt[i];

            if (a * a + b * b - c * c < 0.000001)
                continue;
            else
                return (ld)INF;
        }
    }

    return ret;
}

ll n;
vector<ll> rad;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        rad.push_back(x);
    }
    sort(rad.begin(), rad.end());

    ld ans = INF, E1 = calculate(rad);
    ld k = 10;
    int epochs = 20000;
    while (epochs--)
    {
        ans = min(ans, E1);
        int i = rand() % n, j = rand() % n;
        swap(rad[i], rad[j]);

        ld E2 = calculate(rad);

        if (exp((E1 - E2)) / k > (ld)(rand() % 100) / 100)
            E1 = E2;

        else
            swap(rad[i], rad[j]);

        k *= 0.9999;
    }

    cout << setprecision(10) << ans;
}