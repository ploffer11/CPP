#include <bits/stdc++.h>
using namespace std;

int ans[100005];

class SegmentTree
{
private:
    vector<int> tree;

    void init(int i, int s, int e)
    {
        if (s == e)
        {
            tree[i] = 1;
            return;
        }

        int m = (s + e) / 2;
        init(2 * i, s, m);
        init(2 * i + 1, m + 1, e);

        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n);
        init(1, 1, n);
    }

    int kth(int i, int s, int e, int sum)
    {
        if (s == e)
            return s;
        int m = (s + e) / 2;

        if (tree[2 * i] < sum)
            return kth(2 * i + 1, m + 1, e, sum - tree[2 * i]);
        else
            return kth(2 * i, s, m, sum);
    }

    void update(int i, int s, int e, int idx, int diff)
    {
        if (!(s <= idx && idx <= e))
            return;

        if (s == e)
        {
            tree[i] += diff;
            return;
        }

        int m = (s + e) / 2;
        update(2 * i, s, m, idx, diff);
        update(2 * i + 1, m + 1, e, idx, diff);

        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    SegmentTree Tree(n);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        int j = Tree.kth(1, 1, n, x + 1);
        ans[j] = i;
        Tree.update(1, 1, n, j, -1);
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}