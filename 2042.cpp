#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class FenwickTree
{
private:
    vector<ll> tree;
    int n;

public:
    FenwickTree(int n)
    {
        tree.resize(4 * n, 0);
        this->n = n;
    }

    void update(int i, int x)
    {
        while (i <= n)
        {
            tree[i] += x;
            i += -i & i;
        }
    }

    ll query(int i)
    {
        ll ret = 0;
        while (i)
        {
            ret += tree[i];
            i -= -i & i;
        }
        return ret;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    FenwickTree Tree(n);
    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        arr[i] = x;
        Tree.update(i, x);
    }

    for (int i = 0; i < m + k; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        if (x == 1)
        {
            Tree.update(y, z - arr[y]);
            arr[y] = z;
        }
        else
        {
            cout << Tree.query(z) - Tree.query(y - 1) << '\n';
        }
    }
}