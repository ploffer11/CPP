#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> degree(n + 1, 0);

    while (--n)
    {
        int a, b;
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
    }

    int ans = -1;
    for (auto i : degree)
    {
        ans = max(ans, i + 1);
    }

    cout << ans;
}