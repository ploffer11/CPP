#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class DynamicSegmentTree
{
private:
    struct Node
    {
        int l, r;
        ll value, lazy;
        Node() : l(0), r(0), value(0), lazy(0) {}
    };
    int s, e;
    vector<Node> tree;

    void update_lazy(int i, int s, int e)
    {
        if (tree[i].lazy)
        {
            tree[i].value += (e - s + 1) * tree[i].lazy;
            if (s != e)
            {
                if (tree[i].l == 0)
                {
                    tree[i].l = tree.size();
                    tree.push_back(Node());
                }

                if (tree[i].r == 0)
                {
                    tree[i].r = tree.size();
                    tree.push_back(Node());
                }

                tree[tree[i].l].lazy += tree[i].lazy;
                tree[tree[i].r].lazy += tree[i].lazy;
            }
            tree[i].lazy = 0;
        }
    }

    void _update_idx(int i, int s, int e, int idx, int diff)
    {
        update_lazy(i, s, e);
        if (s == e)
        {
            tree[i].value += diff;
            return;
        }

        int m = (s + e) / 2;
        if (idx <= m)
        {
            if (tree[i].l == 0)
            {
                tree[i].l = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].l, s, m, idx, diff);
        }
        else
        {
            if (tree[i].r == 0)
            {
                tree[i].r = tree.size();
                tree.push_back(Node());
            }
            _update_idx(tree[i].r, m + 1, e, idx, diff);
        }
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    void _update_range(int i, int s, int e, int l, int r, int diff)
    {
        update_lazy(i, s, e);
        if (e < l || s > r)
            return;

        if (l <= s && e <= r)
        {
            tree[i].lazy += diff;
            update_lazy(i, s, e);
            return;
        }

        int m = (s + e) / 2;

        if (tree[i].l == 0)
        {
            tree[i].l = tree.size();
            tree.push_back(Node());
        }

        if (tree[i].r == 0)
        {
            tree[i].r = tree.size();
            tree.push_back(Node());
        }

        _update_range(tree[i].l, s, m, l, r, diff);
        _update_range(tree[i].r, m + 1, e, l, r, diff);
        tree[i].value = tree[tree[i].l].value + tree[tree[i].r].value;
    }

    ll _query(int i, int s, int e, int l, int r)
    {
        update_lazy(i, s, e);
        if (i == 0 || e < l || s > r)
            return 0;
        else if (l <= s && e <= r)
            return tree[i].value;
        else
        {
            int m = (s + e) / 2;
            return _query(tree[i].l, s, m, l, r) + _query(tree[i].r, m + 1, e, l, r);
        }
    }

public:
    DynamicSegmentTree(int e = 1e9 + 7)
    {
        tree.push_back(Node());
        tree.push_back(Node());
        this->s = 1;
        this->e = e;
    }

    ll query(int l, int r)
    {
        return _query(1, s, e, l, r);
    }

    void update_idx(int idx, int diff)
    {
        _update_idx(1, s, e, idx, diff);
    }

    void update_range(int l, int r, int diff)
    {
        _update_range(1, s, e, l, r, diff);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    DynamicSegmentTree Tree;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Tree.update_idx(i, x);
    }

    int j = m + k;
    while (j--)
    {
        int q;
        cin >> q;

        if (q == 1)
        {
            int a, b, c;
            cin >> a >> b >> c;
            Tree.update_range(a, b, c);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << Tree.query(a, b) << endl;
        }
    }
}