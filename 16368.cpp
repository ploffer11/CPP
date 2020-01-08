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

class SegmentTree
{
private:
    vector<ll> tree, lazy;
    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += (e - s + 1) * lazy[i];
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        update_lazy(i, s, e);
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update_range(int i, int s, int e, int l, int r, ll diff)
    {
        update_lazy(i, s, e);

        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
        {
            lazy[i] += diff;
            update_lazy(i, s, e);
        }

        else
        {
            int m = (s + e) / 2;
            update_range(2 * i, s, m, l, r, diff);
            update_range(2 * i + 1, m + 1, e, l, r, diff);
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (s > r || e < l)
            return 0;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return query(2 * i, s, m, l, r) + query(2 * i + 1, m + 1, e, l, r);
        }
    }
    int kth(int i, int s, int e, ll sum)
    {
        if (s == e)
            return s;
        int m = (s + e) / 2;
        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }
};

int work[2005], can[2005];
vector<pii> people[2005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    SegmentTree Tree(5000);

    int m, n, w, h;
    cin >> m >> n >> w >> h;

    for (int i = 1; i <= m; i++)
    {
        cin >> can[i];
        can[i] /= w;
    }

    for (int i = 1; i <= n; i++)
        cin >> work[i];

    for (int i = 1; i <= n; i++)
    {
        int q = Tree.query(1, 1, 5000, i, i);

        if (q > work[i])
        {
            cout << "-1";
            return 0;
        }

        else if (q == work[i])
            continue;

        for (int t = 1; t <= work[i] - q; t++)
        {
            tuple<int, int, int> p = {INF, INF, INF};
            for (int j = 1; j <= m; j++)
            {
                if (!can[j])
                    continue;

                if (people[j].empty())
                {
                    p = min(p, {0, can[j], j});
                }

                if (!people[j].empty() && people[j].back().second + h + 1 <= i)
                {
                    p = min(p, {people[j].back().second, can[j], j});
                }
            }

            auto [a, b, c] = p;

            cout << i << " " << i + w - 1 << "<->" << a << " " << b << " " << c << "\n";
            if (a == INF)
            {
                cout << "-1";
                return 0;
            }

            else
            {
                Tree.update_range(1, 1, 5000, i, i + w - 1, 1);
                can[c]--;
                people[c].push_back({i, i + w - 1});
            }
        }
    }

    cout << "1\n";
    for (int i = 1; i <= m; i++)
    {
        if (!people[i].empty())
        {
            for (auto [s, e] : people[i])
                cout << s << " ";
            cout << "\n";
        }
    }
}