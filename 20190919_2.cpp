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

class FenwickTree
{
private:
    int n;
    vector<ll> tree;

    ll _query(int idx)
    {
        ll ret = 0;
        while (idx)
        {
            ret += tree[idx];
            idx -= (-idx & idx);
        }
        return ret;
    }

public:
    FenwickTree(int n) : n(n)
    {
        tree.resize(n + 10, 0);
    }

    void update(int idx, ll diff)
    {
        while (idx <= n)
        {
            tree[idx] += diff;
            idx += (-idx & idx);
        }
    }

    ll query(int l, int r)
    {
        return _query(r) - _query(l - 1);
    }
};

const int MAX = 1 << 20;
vector<FenwickTree> Tree;
int arr[400005];
ll dp[MAX];
int cnt[21];

int count(int mask)
{
    int ret = 0;
    for (int i = 0; i < 20; i++)
        if (mask & (1 << i))
            ret++;
    return ret;
}

int f(int mask)
{
    int ret = 0;
    for (int i = 0; i < 20; i++)
        if (mask & (1 << i))
            ret += cnt[i];
    return ret;
}

pii g(int idx)
{
    int ret1 = 0, ret2 = 0;
    for (int i = 0; i < idx; i++)
    {
        ret1 += (1 << i);
        ret2 += (1 << (19 - i));
    }
    return {ret1, ret2};
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, 0x3f, sizeof(dp));

    int n;
    cin >> n;

    Tree.resize(21, FenwickTree(n));
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Tree[--x].update(i, 1);
        cnt[x]++;
    }

    for (int i = 0; i < 20; i++)
        dp[1 << i] = cnt[i] - Tree[i].query(1, cnt[i]);

    for (int i = 2; i <= 20; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (count(j) == i)
            {
                for (int k = 0; k < 20; k++)
                {
                    if (j & (1 << k))
                    {
                        int x = j ^ (1 << k);
                        int y = f(x);
                        ll z = 0;
                        for (int m = 0; m < 20; m++)
                            if (x & (1 << m))
                                z += Tree[m].query(y + 1, y + cnt[k]);

                        dp[j] = min(dp[j], dp[x] + cnt[k] - min(z, Tree[k].query(1, y)) - Tree[k].query(y + 1, y + cnt[k]));
                    }
                }
            }
        }
    }

    cout << dp[MAX - 1];
}