#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int, int>;
const int INF = 987654321;

class SegmentTree
{
private:
    vector<int> tree, lazy;

public:
    SegmentTree(int n)
    {
        lazy.resize(4 * n, 0);
        tree.resize(4 * n, 0);
    }

    void update(int i, int s, int e, int l, int r, int diff)
    {
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
            lazy[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update(2 * i, s, m, l, r, diff);
            update(2 * i + 1, m + 1, e, l, r, diff);
        }

        if (lazy[i] > 0)
            tree[i] = e - s + 1;
        else if (lazy[i] == 0 && s != e)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        else if (lazy[i] == 0 && s == e)
            tree[i] = 0;
    }

    int query()
    {
        return tree[1];
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    const int START = 0, END = 1;
    SegmentTree Tree(30005);

    int n;
    cin >> n;
    vector<t> querys;

    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        querys.push_back(t(x1, y1, y2, START));
        querys.push_back(t(x2, y1, y2, END));
    }

    sort(querys.begin(), querys.end());

    ll prev = get<0>(querys[0]);
    ll ans = 0;

    for (auto [x, l, r, query] : querys)
    {
        ans += 1LL * (x - prev) * Tree.query();
        prev = x;

        if (query == START)
            Tree.update(1, 0, 30000, l, r - 1, 1);

        else if (query == END)
            Tree.update(1, 0, 30000, l, r - 1, -1);
    }

    cout << ans;
}