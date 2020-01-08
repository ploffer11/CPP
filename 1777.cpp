#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
    vector<int> tree, arr;

    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        arr.resize(n + 1, 1);
        init(1, 1, n);
    }

    void init(int node, int s, int e)
    {
        if (s == e)
        {
            tree[node] = arr[s];
            return;
        }

        int m = (s + e) / 2;
        init(2 * node, s, m);
        init(2 * node + 1, m + 1, e);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int s, int e, int i, int diff)
    {
        if (!(s <= i && i <= e))
            return;

        if (s == e)
        {
            tree[node] += diff;
            return;
        }

        int m = (s + e) / 2;
        update(2 * node, s, m, i, diff);
        update(2 * node + 1, m + 1, e, i, diff);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int kth(int node, int s, int e, int k)
    {
        if (s == e)
            return s;

        int m = (s + e) / 2;

        if (tree[2 * node] < k)
            return kth(2 * node + 1, m + 1, e, k - tree[2 * node]);
        else
            return kth(2 * node, s, m, k);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> vt(n);
    vector<int> ans(n + 1, -1);

    for (int i = 0; i < n; i++)
        cin >> vt[i];

    SegmentTree Tree(n);

    for (int i = n - 1; i >= 0; i--)
    {
        int j = Tree.kth(1, 1, n, vt[i] + 1);
        ans[j] = i + 1;
        Tree.update(1, 1, n, j, -1);
    }

    for (int i = n; i >= 1; i--)
        cout << ans[i] << " ";
}