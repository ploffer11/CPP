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

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int i, n, arr[100], x = 0;
    cin >> n;
    for (i = 0; i < n;i++)
    {
        cin >> arr[i];
        x += arr[i];
    }

    cout << x << "\n";
    for (int i = 0; i < 3;i++){
        if(i%2==0){
            printf("%d", i);
            printf("%d %d\n", i, i);
        }
    }
}