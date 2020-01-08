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
    vector<int> tree;

public:
    vector<int> arr;
    SegmentTree(int n)
    {
        tree.resize(6 * n, INF);
        arr.resize(n + 2, 0);
    }

    void init(int i, int s, int e)
    {
        if (s == e)
            tree[i] = arr[s];
        else
        {
            int m = (s + e) / 2;
            init(2 * i, s, m);
            init(2 * i + 1, m + 1, e);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = diff;
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    ll query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return min(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

int ans[300005], dp[300005];
char inp[300005];

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        SegmentTree Tree(n);
        for (int i = 1; i <= n; i++)
        {
            cin >> inp[i];
            Tree.arr[i] = inp[i] - '0';
        }

        Tree.init(1, 1, n);

        dp[n] = inp[n] - '0';
        for (int i = n - 1; i >= 1; i--)
        {
            dp[i] = min(dp[i + 1], inp[i] - '0');
        }

        for (int i = 1; i <= n; i++)
        {
            int cur = inp[i] - '0';
            ll q1 = Tree.query(1, 1, n, 1, i);
            ll q2 = dp[i];

            //cout << cur << " " << q1 << " " << q2 << "\n";
            if (q1 >= cur && cur <= q2)
            {
                ans[i] = 1;
                Tree.update_idx(1, 1, n, i, INF);
            }
            else
                ans[i] = 2;
        }

        vector<int> vt;

        for (int i = 1; i <= n; i++)
            if (ans[i] == 1)
                vt.push_back(inp[i] - '0');

        for (int i = 1; i <= n; i++)
            if (ans[i] == 2)
                vt.push_back(inp[i] - '0');

        //for (auto i : vt)
        //    cout << i << " -> ";
        //cout << "\n";

        bool flag = true;
        for (int i = 0; i < n - 1; i++)
            if (vt[i] > vt[i + 1])
                flag = false;

        if (flag)
        {
            for (int i = 1; i <= n; i++)
                cout << ans[i];
            cout << "\n";
        }
        else
        {
            cout << "-\n";
        }
    }
}