#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = -1;

ll get_kth(ll first, ll second, ll k)
{
    // cout << "get_kth: " << first << " " << second << " " << k << endl;
    if (k <= 4)
    {
        if (k == 1)
            return first;
        if (k == 2)
            return second;
        if (k == 3)
            return abs(first - second);
        if (k == 4)
            return abs(abs(first - second) - second);
    }
    
    if (second == 0)
    {
        if ((k - 2) % 3 == 0)
            return 0;
        else 
            return first;
    }
    
    if (first == 0)
    {
        if ((k - 1) % 3 == 0)
            return 0;
        else 
            return second;
    }
    
    if (first >= second)
        return get_kth(abs(first - second), abs(abs(first - second) - second), k - 2);
    
    
    ll x = ceil((double)(second - first) / first);
    ll idx = 3 * (x / 2) + 2 + (x % 2 == 1);

    if (k - idx <= 0) 
    {
        if ((k - 1) % 3 == 0)
            return first;
        ll y = (k - 1) - (k + 2) / 3;
        return second - first * y;
    }
    
    if (x % 2 == 0)
    {
        return get_kth(first, second - x * first, k - idx + 2);
    }
    else
    {
        return get_kth(second - x * first, first, k - idx + 1);
    }
}


main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    ll first, second, q;
    cin >> first >> second >> q;
    // cout << "wtwRDASDADASDA" << endl;
    
    while (q--)
    {
        ll k;
        cin >> k;
        cout << get_kth(first, second, k + 1) << "\n";
        
        // ll f = first, s = second;
        // ll j = k;
        // while (j--)
        // {
        //     ll temp = abs(s - f);
        //     f = s;
        //     s = temp;
        // }
        
        // ll temp = get_kth(first, second, k + 1);
        // if (f != temp)
        //     cout << k << " -> " << f << " != " << temp << endl;
        // else 
        //     cout << k << " -> " << f << " == " << temp << endl;
    }
}

