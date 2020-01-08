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

struct Solve
{
    int ans = 0, k;
    vector<int> arr;

    void dfs(int s, int cur_sum)
    {
        if (cur_sum > k)
            return;
        ans++;
        for (int i = s + 1; i < arr.size(); i++)
            dfs(i, cur_sum + arr[i]);
    }

    Solve(int k) : k(k) {}
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    Solve problem(k);

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        problem.arr.push_back(x);
    }

    problem.dfs(-1, 0);

    cout << problem.ans % 10000;
}