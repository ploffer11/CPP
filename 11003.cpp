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

deque<pii> dq;
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, l;
    cin >> n >> l;

    for (int i = 1; i <= n; i++)
    {
        if (!dq.empty() && dq.front().second <= i - l)
            dq.pop_front();

        int x;
        cin >> x;
        while (!dq.empty() && dq.back().first >= x)
            dq.pop_back();

        dq.push_back({x, i});
        cout << dq.front().first << " ";
    }
}