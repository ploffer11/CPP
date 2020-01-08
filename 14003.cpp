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
    vector<pair<int, int>> tree;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, {0, 0});
    }

    void update_idx(int i, int s, int e, int idx, ll diff)
    {
        if (!(s <= idx && idx <= e))
            return;
        else if (s == e)
            tree[i] = {diff, s};
        else
        {
            int m = (s + e) / 2;
            update_idx(2 * i, s, m, idx, diff);
            update_idx(2 * i + 1, m + 1, e, idx, diff);
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    pii query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return {-INF, -INF};
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

vector<int> vt[1000005];
vector<pii> arr;
vector<int> cp;
int pre[1000005], num[1000005];
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
        cp.push_back(num[i]);
    }

    sort(cp.begin(), cp.end());
    cp.resize(unique(cp.begin(), cp.end()) - cp.begin());

    for (int i = 1; i <= n; i++)
    {
        vt[lower_bound(cp.begin(), cp.end(), num[i]) - cp.begin() + 1].push_back(i);
    }

    for (int i = 1; i <= n; i++)
    {
        vector<int> save;
        for (auto idx : vt[i])
        {
            auto [m, k] = Tree.query(1, 1, n, 1, idx);
            pre[idx] = k;
            save.push_back(m);
        }

        int z = 0;
        for (auto idx : vt[i])
            Tree.update_idx(1, 1, n, idx, save[z++] + 1);
    }

    auto [ans, e] = Tree.query(1, 1, n, 1, n);

    cout << ans << "\n";

    stack<int> st;
    while (pre[e] > 0)
    {
        st.push(e);
        e = pre[e];
    }
    cout << num[e] << " ";
    while (!st.empty())
    {
        cout << num[st.top()] << " ";
        st.pop();
    }
}

