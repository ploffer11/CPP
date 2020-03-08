#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class PersistentSegmentTree
{
private:
    struct Node
    {
        Node() : v(0), l(0), r(0) {}
        int v, l, r;
    };
    vector<int> x;
    vector<Node> tree;
    vector<vector<int>> y;
    int xs, xe, ys, ye;
    bool flag = true;

    int make_tree(int cur, int ys, int ye, int y, int v)
    {
        if (!(ys <= y && y <= ye))
            return cur;
        int ret = tree.size();
        tree.push_back(Node());
        if (ys == ye)
        {
            tree[ret].v = tree[cur].v + v;
            return ret;
        }
        int ym = (ys + ye) >> 1;
        tree[ret].l = make_tree(tree[cur].l, ys, ym, y, v);
        tree[ret].r = make_tree(tree[cur].r, ym + 1, ye, y, v);
        tree[ret].v = tree[tree[ret].l].v + tree[tree[ret].r].v;
        return ret;
    }

    int dfs(int ys, int ye)
    {
        int ret = tree.size();
        tree.push_back(Node());

        if (ys == ye)
        {
            tree[ret].v = 0;
            return ret;
        }

        int ym = (ys + ye) >> 1;
        tree[ret].l = dfs(ys, ym);
        tree[ret].r = dfs(ym + 1, ye);
        tree[ret].v = tree[tree[ret].l].v + tree[tree[ret].r].v;
        return ret;
    }

    int query(int cur, int ys, int ye, int yl, int yr)
    {
        if (ys > yr || ye < yl || !cur)
            return 0;
        else if ((yl <= ys && ye <= yr))
            return tree[cur].v;
        int ym = (ys + ye) >> 1;
        return query(tree[cur].l, ys, ym, yl, yr) + query(tree[cur].r, ym + 1, ye, yl, yr);
    }

    void init()
    {
        if (!flag)
            return;
        flag = false;
        x[xs] = dfs(ys, ye);

        for (auto i : y[xs])
            x[xs] = make_tree(x[xs], ys, ye, i, 1);

        for (int i = 1; i <= xe; i++)
        {
            if (!y[i].empty())
                for (int j = 0; j < y[i].size(); j++)
                    x[i] = make_tree(x[(j == 0 ? i - 1 : i)], ys, ye, y[i][j], 1);
            else
                x[i] = x[i - 1];
        }
    }

    int kth(int t1, int t2, int ys, int ye, int k)
    {
        int ym = (ys + ye) >> 1;

        if (ys == ye)
            return ys;

        if (tree[tree[t2].l].v - tree[tree[t1].l].v >= k)
            return kth(tree[t1].l, tree[t2].l, ys, ym, k);
        else
            return kth(tree[t1].r, tree[t2].r, ym + 1, ye, k - (tree[tree[t2].l].v - tree[tree[t1].l].v));
    }

public:
    // make_tree [0, n] x [0, n] segment tree
    PersistentSegmentTree(int n) : xs(0), xe(n), ys(0), ye(n), x(n + 1), y(n + 1)
    {
        tree.push_back(Node());
    }

    // add point (x, y)
    void add_point(int x, int y)
    {
        this->y[x].push_back(y);
    }

    // query [xl, xr] x [yl, yr]
    int query(int xl, int xr, int yl, int yr)
    {
        init();
        if (xl == 0)
            return query(x[xr], xs, xe, yl, yr);
        else
            return query(x[xr], xs, xe, yl, yr) - query(x[xl - 1], xs, xe, yl, yr);
    }

    // find min(y) that satisfies query [xl, xr] x [0, y] >= k
    int kth(int xl, int xr, int k)
    {
        init();
        return kth((xl == 0 ? 0 : x[xl - 1]), x[xr], ys, ye, k);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        PersistentSegmentTree tree(100000);
        int n, m;
        cin >> n >> m;
        while (n--)
        {
            int x, y;
            cin >> x >> y;
            tree.add_point(x, y);
        }

        ll ans = 0;
        while (m--)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            ans += tree.query(x1, x2, y1, y2);
        }

        cout << ans << "\n";
    }
}