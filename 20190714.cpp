#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int BOB = 1, ALICE = 2;

map<int, int> dp;
int n, k;

int f(int i)
{
    if (dp[i])
        return dp[i];

    if (i < 0)
        return -1;

    int a = f(i - 1), b = f(i - 2), c = f(i - k);

    if (a == BOB || b == BOB || c == BOB)
        return dp[i] = ALICE;
    else
        return dp[i] = BOB;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--)
    {
        cin >> n >> k;

        dp[0] = BOB;
        dp[1] = dp[2] = dp[k] = ALICE;
        if (f(n) == ALICE)
            cout << "Alice\n";
        else
            cout << "Bob\n";

        dp.clear();
    }
}