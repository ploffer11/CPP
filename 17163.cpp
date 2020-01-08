#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 1'000'001;

class SegmentTree2
{
private:
    vector<ll> tree;

public:
    SegmentTree2(int n)
    {
        tree.resize(4 * n, -1);
    }

    void update_idx(int i, int s, int e, int idx, int diff)
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

vector<int> vt[MAX];
vector<int> arr;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    SegmentTree2 MinTree(MAX);

    int q, mod;
    cin >> q >> mod;

    if (mod >= MAX - 1)
    {
        while (q--)
        {
            int a, b;
            cin >> a;

            if (a == 3)
                cout << "-1\n";
            else if (a == 1)
                cin >> b;
        }
        return 0;
    }

    while (q--)
    {
        int a, b;
        cin >> a;

        if (a == 1)
        {
            cin >> b;
            b %= mod;

            arr.push_back(b);
            MinTree.update_idx(1, 0, MAX, b, arr.size() - 1);
            vt[b].push_back(arr.size() - 1);
        }

        else if (a == 2)
        {
            if (arr.empty())
                continue;

            vt[arr.back()].pop_back();
            if (vt[arr.back()].empty())
                MinTree.update_idx(1, 0, MAX, arr.back(), -1);
            else
                MinTree.update_idx(1, 0, MAX, arr.back(), vt[arr.back()].back());
            arr.pop_back();
        }

        else
        {
            ll idx = MinTree.query(1, 0, MAX, 0, mod - 1);
            cout << (idx == -1 ? -1 : arr.size() - idx) << '\n';
        }
    }
}
