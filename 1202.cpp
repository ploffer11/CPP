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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<pii> arr;
    vector<int> bag;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        arr.push_back({a, b});
    }
    for (int j = 0; j < k; j++)
    {
        int x;
        cin >> x;
        bag.push_back(x);
    }

    sort(arr.begin(), arr.end());
    sort(bag.begin(), bag.end());

    ll ans = 0;
    int j = 0;
    priority_queue<int, vector<int>, less<int>> pq;
    for (int i = 0; i < k; i++)
    {
        while (j < n && bag[i] >= arr[j].first)
            pq.push(arr[j++].second);

        if (!pq.empty())
        {
            ans += pq.top();
            pq.pop();
        }
    }

    cout << ans;
}