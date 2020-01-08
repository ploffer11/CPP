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
const int MAX = 1'000'005;

vector<int> fail;
pii ans[MAX];

void make_fail(vector<int> &p)
{
    int i = 0, j = 0, n = p.size();
    fail.resize(p.size(), 0);
    while (++i < n)
    {
        while (j && p[i] != p[j])
            j = fail[j - 1];
        if (p[i] == p[j])
            fail[i] = ++j;
        int k = n - i - 1, p = (i + 1 - fail[i]);
        ans[i] = {k + p, p};
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> vt(n);

    for (int i = 0; i < n; i++)
        cin >> vt[i];

    reverse(vt.begin(), vt.end());
    make_fail(vt);

    pii x = {n, 1};
    for (int i = 1; i < n; i++)
    {
        x = min(x, ans[i]);
    }

    cout << x.first - x.second << " " << x.second;
}