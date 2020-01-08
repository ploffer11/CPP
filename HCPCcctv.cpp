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
    SegmentTree(int n)
    {
        tree.resize(4 * (n + 1), 0);
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
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    int query(int i, int s, int e, int l, int r)
    {
        if (s > r || e < l)
            return -INF;
        else if (l <= s && e <= r)
            return tree[i];
        else
        {
            int m = (s + e) / 2;
            return max(query(2 * i, s, m, l, r), query(2 * i + 1, m + 1, e, l, r));
        }
    }
};

vector<SegmentTree> SegR, SegC;
const int DOWN = 1;
const int UP = 2;
const int LEFT = 3;
const int RIGHT = 4;

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    for (int i = 0; i < 301; i++)
    {
        SegR.push_back(*(new SegmentTree(301)));
        SegC.push_back(*(new SegmentTree(301)));
    }

    int R, C;
    cin >> R >> C;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            int x;
            cin >> x;
            SegR[i].update_idx(1, 1, C, j, x);
            SegC[j].update_idx(1, 1, R, i, x);
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int x, y, r, c, k, d;
        cin >> x >> y >> r >> c >> k >> d;

        k--;
        int rl = x, rr = x + r - 1;
        int cl = y, cr = y + c - 1;

        deque<pii> dq;

        vector<int> query;
        switch (d)
        {
        case DOWN:
            for (int i = rl; i <= rr + k; i++)
            {
                int w = SegR[i].query(1, 1, C, cl, cr);
                while (!dq.empty() && dq.back().second <= w)
                    dq.pop_back();

                if (!dq.empty() && dq.front().first <= i - r)
                    dq.pop_front();
                dq.push_back({i, w});

                query.push_back(dq.front().second);
            }
            break;

        case UP:
            for (int i = rr; i >= rl - k; i--)
            {
                int w = SegR[i].query(1, 1, C, cl, cr);
                while (!dq.empty() && dq.back().second <= w)
                    dq.pop_back();

                if (!dq.empty() && dq.front().first >= i + r)
                    dq.pop_front();
                dq.push_back({i, w});

                query.push_back(dq.front().second);
            }
            break;

        case LEFT:
            for (int i = cl; i <= cr + k; i++)
            {
                int w = SegC[i].query(1, 1, R, rl, rr);
                while (!dq.empty() && dq.back().second <= w)
                    dq.pop_back();

                if (!dq.empty() && dq.front().first <= i - c)
                    dq.pop_front();
                dq.push_back({i, w});

                query.push_back(dq.front().second);
            }
            break;

        case RIGHT:
            for (int i = cr; i >= cl - k; i--)
            {
                int w = SegC[i].query(1, 1, R, rl, rr);
                while (!dq.empty() && dq.back().second <= w)
                    dq.pop_back();

                if (!dq.empty() && dq.front().first >= i + c)
                    dq.pop_front();
                dq.push_back({i, w});

                query.push_back(dq.front().second);
            }
            break;
        }

        int ans = 0;
        if (d == UP || d == DOWN)
        {
            for (int i = r - 1; i < query.size(); i++)
                ans ^= query[i];
        }
        else
        {
            for (int i = c - 1; i < query.size(); i++)
                ans ^= query[i];
        }

        cout << ans << "\n";
    }
}