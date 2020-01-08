#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

vector<pll> vt;

ll a[100'005], b[100'005];
vector<ll> arr[100'005];
vector<ll> cp;

ll p = 0;

bool cmp(ll a1, ll a2)
{
    if (a1 < p)
        a1 += 30 * ((p - a1) / 30 + ((p - a1) % 30 == 0 ? 0 : 1));

    if (a2 < p)
        a2 += 30 * ((p - a2) / 30 + ((p - a2) % 30 == 0 ? 0 : 1));

    return a1 < a2;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        cp.push_back(b[i]);
    }

    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());

    for (int i = 0; i < n; i++)
    {
        int c = lower_bound(cp.begin(), cp.end(), b[i]) - cp.begin();
        arr[c].push_back(a[i]);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        int B = cp[i];

        sort(arr[i].begin(), arr[i].end(), cmp);
        for (auto a : arr[i])
        {
            //cout << B << " " << a << " " << p << '\n';
            if (a < B)
            {
                ll cnt = (B - a) / 30 + ((B - a) % 30 == 0 ? 0 : 1);
                ans += cnt;
                a += cnt * 30;
            }

            if (a < p)
            {
                ll cnt = (p - a) / 30 + ((p - a) % 30 == 0 ? 0 : 1);
                ans += cnt;
                a += cnt * 30;
            }

            p = a;
        }
    }

    cout << ans;
}