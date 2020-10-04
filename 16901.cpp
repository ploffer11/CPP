#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const int INF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 200001;

#define zero first
#define one second

#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.resize(unique(all(x)) - x.begin()); 
#define compress_function(x, f) auto f = [&](ll k){ return lower_bound(all(x), k) - x.begin(); };


int cnt;
pii nxt[10000000];

int get_min(int i, int x, int cur_bit)
{
    // cout << i << " " << x << " " << cur_bit << endl;
    if ((1 << (cur_bit)) & x)
    {
        if (nxt[i].one)
            return get_min(nxt[i].one, x, cur_bit - 1);
        else if (nxt[i].zero)
            return (1 << cur_bit) + get_min(nxt[i].zero, x, cur_bit - 1);
        else 
            return 0;
    }
    else 
    {
        if (nxt[i].zero)
            return get_min(nxt[i].zero, x, cur_bit - 1);
        else if (nxt[i].one)
            return (1 << cur_bit) + get_min(nxt[i].one, x, cur_bit - 1);
        else 
            return 0;
    }
}

void update(int i, int x, int cur_bit)
{
    if (cur_bit < 0)
        return;
    
    if ((1 << cur_bit) & x)
    {
        if (!nxt[i].one)
            nxt[i].one = ++cnt;
        update(nxt[i].one, x, cur_bit - 1);
    }
    else
    {
        if (!nxt[i].zero)
            nxt[i].zero = ++cnt;
        update(nxt[i].zero, x, cur_bit - 1);
    }
}

ll ans = 0;

struct Trie2
{
    vector<int> vt;
    pair<Trie2*, Trie2*> next;
    
    void solve(int bit = 30)
    {
        if (bit == -1)
            return;
        
        while (!vt.empty())
        {
            int x = vt.back();
            vt.pop_back();
            if ((1 << bit) & x)
            {
                if (!next.one)
                    next.one = new Trie2();
                next.one->vt.push_back(x);
            }
            else 
            {
                if (!next.zero)
                    next.zero = new Trie2();
                next.zero->vt.push_back(x);
            }
        }
        
        
        if (next.zero && next.one)
        {
            auto &L = next.zero->vt;
            auto &R = next.one->vt;
            
            for (auto i : L)
                update(0, i, bit);
            ll x = INF;
            for (auto i : R)
                x = min(x, (ll)get_min(0, i, bit));
            ans += x;
            
            for (int i = 0; i <= cnt; i++)
                nxt[i] = {0, 0};
            cnt = 0;
            
        }
        
        if (next.first)
            next.first->solve(bit - 1);
        if (next.second)
            next.second->solve(bit - 1);
    }
};
// 9378257794
main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n;
    cin >> n;
    
    
    Trie2 trie;
    for (int i = 0, x; i < n; i++)
    {
        cin >> x;
        trie.vt.push_back(x);
    }
    
    trie.solve();
    cout << ans << "\n";
}