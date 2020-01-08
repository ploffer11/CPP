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

int f(const string &x)
{
    int ret = 0;
    for (auto i : x)
        ret |= (1 << (i - 'a'));
    return ret;
}

int mask = -1;

void add(char x)
{
    mask |= (1 << (x - 'a'));
}

void del(char x)
{
    mask ^= (1 << (x - 'a'));
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    vector<string> vt(n);
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> vt[i];
        sort(vt[i].begin(), vt[i].end());
        vt[i].resize(unique(vt[i].begin(), vt[i].end()) - vt[i].begin());
        arr[i] = f(vt[i]);
    }

    while (q--)
    {
        int x;
        char y;
        cin >> x >> y;
        if (x == 1)
            del(y);
        else
            add(y);

        int cnt = 0;
        for (auto i : arr)
            if ((mask & i) == i)
                cnt++;

        cout << cnt << "\n";
    }
}