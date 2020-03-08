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

class MinSegmentTree
{
private:
    vector<pii> tree;

public:
    MinSegmentTree(int n)
    {
        tree.resize(4 * (n + 1), pii(-1, 0));
    }

    void update_idx(int i, int s, int e, int idx)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
        {
            auto [x, y] = tree[i];
            tree[i] = {x + 1, idx};
        }
        else
        {
            int m = (s + e) >> 1;
            update_idx(2 * i, s, m, idx);
            update_idx(2 * i + 1, m + 1, e, idx);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    pii query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return pii(INF, INF);
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) >> 1;
            return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

vector<int> arr[200005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int x;
            cin >> x;
            if ((x - j) % m == 0)
            {
                int y = (x - j) / m;
                if (0 <= y && y < n)
                    arr[j].push_back(y);
                else
                    arr[j].push_back(-1);
            }
            else
            {
                arr[j].push_back(-1);
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        vector<int> cnt(n, 0);
        for (int j = 0; j < arr[i].size(); j++)
        {
            if (arr[i][j] != -1)
            {
                if (j - arr[i][j] >= 0)
                    cnt[j - arr[i][j]]++;
                else
                    cnt[n - (arr[i][j] - j)]++;
            }
        }

        int k = INF;

        for (int j = 0; j < n; j++)
            k = min(n - cnt[j] + j, k);

        ans += k;
    }
    cout << ans;
}