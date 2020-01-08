#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class SegmentTree
{
private:
    vector<ll> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
    }

    void update_idx(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

int money[200005];
int last_query[200005];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    SegmentTree Tree(200005);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> money[i];
    }

    int q;
    cin >> q;

    for (int i = 1; i <= q; i++)
    {
        int c;
        cin >> c;
        if (c == 1)
        {
            int x, y;
            cin >> x >> y;
            last_query[x] = i;
            money[x] = y;
        }

        else
        {
            int x;
            cin >> x;
            Tree.update_idx(1, 1, q, i, x);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int query = Tree.query(1, 1, q, last_query[i], q);
        //cout << money[i] << " < - > " << query << endl;
        cout << max(money[i], query) << " ";
    }
}