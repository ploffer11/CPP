#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

vector<ll> A, B;
int n, s;
int arr[50];

void f(int depth, int max_depth, int i, ll sum, bool flag)
{
    if (max_depth - depth > (flag ? n / 2 : n) - i)
    {
        return;
    }

    if (depth == max_depth)
    {
        (flag ? A : B).push_back(sum);
        return;
    }

    for (int j = i + 1; j <= (flag ? n / 2 : n); j++)
    {
        f(depth + 1, max_depth, j, sum + arr[j], flag);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> s;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    for (int i = 0; i <= n / 2; i++)
        f(0, i, 0, 0, true);

    for (int i = 0; i <= n / 2 + (n % 2); i++)
        f(0, i, n / 2, 0, false);

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<pair<ll, ll>> vt1, vt2;
    for (auto i : A)
    {
        if (vt1.empty() || vt1.back().first != i)
            vt1.push_back({i, 1});
        else
            vt1.back().second++;
    }

    for (auto i : B)
    {
        if (vt2.empty() || vt2.back().first != i)
            vt2.push_back({i, 1});
        else
            vt2.back().second++;
    }

    reverse(vt2.begin(), vt2.end());

    int i = 0, j = 0;
    ll ans = 0;
    while (i < vt1.size() && j < vt2.size())
    {

        if (vt1[i].first + vt2[j].first == s)
            ans += vt1[i++].second * vt2[j++].second;
        else if (vt1[i].first + vt2[j].first < s)
            i++;
        else
            j++;
    }

    cout << ans - (s == 0);
}