#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

class FenwickTree2D
{
private:
    vector<vector<int>> tree;
    int n;

public:
    FenwickTree2D(int n)
    {
        this->n = n;
        tree.resize(n + 1);
        for (int i = 1; i <= n; i++)
            tree[i].resize(n + 1);
    }

    void update(int x, int y, int diff)
    {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                tree[i][j] += diff;
    }

    int query(int x, int y)
    {
        int ret = 0;

        for (int i = x; i >= 1; i -= i & -i)
            for (int j = y; j >= 1; j -= j & -j)
                ret += tree[i][j];

        return ret;
    }
};

int arr[1100][1100];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    FenwickTree2D FenwickTree(n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            FenwickTree.update(i, j, x);
            arr[i][j] = x;
        }
    }

    while (m--)
    {
        int q;
        cin >> q;

        if (q)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << FenwickTree.query(x2, y2) + FenwickTree.query(x1 - 1, y1 - 1) - FenwickTree.query(x1 - 1, y2) - FenwickTree.query(x2, y1 - 1) << '\n';
        }

        else
        {
            int x, y, c;
            cin >> x >> y >> c;
            FenwickTree.update(x, y, c - arr[x][y]);
            arr[x][y] = c;
        }
    }
}