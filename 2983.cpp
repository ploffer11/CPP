#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 12345678987654321;
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
        tree.resize(4 * (n + 1), 0);
        lazy.resize(4 * (n + 1), 0);
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

int n;
bool flag_x[100'005], flag_y[100'005];
vector<int> x_y[100'005], y_x[100'005];
map<int, SegmentTree *> x_y2, y_x2;

void remove_xy(int x, int y)
{
    if (flag_x[x])
    {
        x_y2[x]->update_idx(1, 1, n, y, -1);
    }

    else
    {
        auto it = lower_bound(x_y[x].begin(), x_y[x].end(), y);
        x_y[x].erase(it);
    }

    if (flag_y[y])
    {
        y_x2[y]->update_idx(1, 1, n, x, -1);
    }

    else
    {
        auto it = lower_bound(y_x[y].begin(), y_x[y].end(), x);
        y_x[y].erase(it);
    }
}
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    string inp;
    int k, x, y;
    cin >> n >> k >> inp >> x >> y;

    y -= x;
    x = y + 2 * x;

    vector<pii> plant;
    vector<int> plant_x, plant_y;
    plant.push_back({x, y});
    plant_x.push_back(x);
    plant_y.push_back(y);

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        plant.push_back({u + v, -u + v});
        plant_x.push_back(u + v);
        plant_y.push_back(-u + v);
    }

    sort(plant_x.begin(), plant_x.end());
    sort(plant_y.begin(), plant_y.end());
    plant_x.resize(unique(plant_x.begin(), plant_x.end()) - plant_x.begin());
    plant_y.resize(unique(plant_y.begin(), plant_y.end()) - plant_y.begin());

    for (auto &[x, y] : plant)
    {
        x = lower_bound(plant_x.begin(), plant_x.end(), x) - plant_x.begin() + 1;
        y = lower_bound(plant_y.begin(), plant_y.end(), y) - plant_y.begin() + 1;

        x_y[x].push_back(y);
        y_x[y].push_back(x);
    }

    x = plant[0].first, y = plant[0].second;

    for (int i = 1; i <= n; i++)
    {
        if (x_y[i].size() >= 1000)
        {
            flag_x[i] = true;
            x_y2[i] = new SegmentTree(n);
            for (auto y : x_y[i])
                x_y2[i]->update_idx(1, 1, n, y, 1);
        }
        else
            sort(x_y[i].begin(), x_y[i].end());

        if (y_x[i].size() >= 1000)
        {
            flag_y[i] = true;
            y_x2[i] = new SegmentTree(n);
            for (auto x : y_x[i])
                y_x2[i]->update_idx(1, 1, n, x, 1);
        }
        else
            sort(y_x[i].begin(), y_x[i].end());
    }

    for (auto i : inp)
    {
        //cout << x << " " << y << " " << i << endl;
        if (i == 'A')
        {
            if (flag_y[y])
            {
                auto &tree = *y_x2[y];
                int q = tree.query(1, 1, n, 1, x);
                if (q == tree.query(1, 1, n, 1, n))
                    continue;

                int k = tree.kth(1, 1, n, q + 1);
                remove_xy(x, y);
                x = k;
            }
            else
            {
                int j = lower_bound(y_x[y].begin(), y_x[y].end(), x) - y_x[y].begin();

                if (j == y_x[y].size() - 1)
                    continue;

                int temp = x;
                x = y_x[y][j + 1];
                remove_xy(temp, y);
            }
        }

        else if (i == 'B')
        {
            if (flag_x[x])
            {
                auto &tree = *x_y2[x];
                int q = tree.query(1, 1, n, 1, y);

                if (q == 1)
                    continue;

                int k = tree.kth(1, 1, n, q - 1);
                remove_xy(x, y);
                y = k;
            }
            else
            {
                int j = lower_bound(x_y[x].begin(), x_y[x].end(), y) - x_y[x].begin();

                if (j == 0)
                    continue;

                int temp = y;
                y = x_y[x][j - 1];
                remove_xy(x, temp);
            }
        }

        else if (i == 'C')
        {
            if (flag_x[x])
            {
                auto &tree = *x_y2[x];
                int q = tree.query(1, 1, n, 1, y);

                if (q == tree.query(1, 1, n, 1, n))
                    continue;

                int k = tree.kth(1, 1, n, q + 1);
                remove_xy(x, y);
                y = k;
            }
            else
            {
                int j = lower_bound(x_y[x].begin(), x_y[x].end(), y) - x_y[x].begin();

                if (j == x_y[x].size() - 1)
                    continue;

                int temp = y;
                y = x_y[x][j + 1];
                remove_xy(x, temp);
            }
        }

        else if (i == 'D')
        {
            if (flag_y[y])
            {
                auto &tree = *y_x2[y];
                int q = tree.query(1, 1, n, 1, x);
                if (q == 1)
                    continue;

                int k = tree.kth(1, 1, n, q - 1);
                remove_xy(x, y);
                x = k;
            }
            else
            {
                int j = lower_bound(y_x[y].begin(), y_x[y].end(), x) - y_x[y].begin();

                if (j == 0)
                    continue;

                int temp = x;
                x = y_x[y][j - 1];
                remove_xy(temp, y);
            }
        }
    }

    x = plant_x[x - 1];
    y = plant_y[y - 1];

    cout << (x - y) / 2 << " " << (x + y) / 2 << "\n";
}