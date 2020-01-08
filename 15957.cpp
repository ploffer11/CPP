#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using t = tuple<int, int, int>;
const int N = 100005;
const int INF = 987654321;

vector<t> score;
vector<int> adj[N], singer[N];
pii pbs[N], range[N];
int sz[N], visit[N], singer_of_song[N];
int n, k, J, cnt;

class SegmentTree
{
private:
    vector<ll> tree, lazy;

public:
    SegmentTree(int n)
    {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void update(int i, int s, int e, int l, int r, int diff)
    {
        if (s > r || e < l)
            return;
        else if (l <= s && e <= r)
            lazy[i] += diff;
        else
        {
            int m = (s + e) / 2;
            update(2 * i, s, m, l, r, diff);
            update(2 * i + 1, m + 1, e, l, r, diff);
        }
    }

    void update_lazy(int i, int s, int e)
    {
        if (lazy[i] != 0)
        {
            tree[i] += lazy[i] * (e - s + 1);
            if (s != e)
            {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    ll query(int i, int s, int e, int idx)
    {
        update_lazy(i, s, e);

        if (!(s <= idx && idx <= e))
            return 0;
        else if (s == e)
            return tree[i];

        int m = (s + e) / 2;
        return query(2 * i, s, m, idx) + query(2 * i + 1, m + 1, e, idx);
    }
};

int dfs_numbering(int s)
{
    visit[s] = ++cnt;
    int m = visit[s];

    for (auto e : adj[s])
        if (!visit[e])
            m = max(m, dfs_numbering(e));

    sz[s] = m - visit[s] + 1;
    range[s] = {visit[s], m};
    return m;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k >> J;
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        singer_of_song[i] = x;
        singer[x].push_back(i);
        pbs[i] = {0, k - 1};
    }

    for (int i = 0; i < k; i++)
    {
        int t, s, p;
        cin >> t >> s >> p;
        score.push_back({t, s, p});
    }

    sort(score.begin(), score.end());
    dfs_numbering(1);

    while (1)
    {
        vector<int> mid[N];
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            auto [s, e] = pbs[i];
            if (s <= e && singer[i].size() > 0)
            {
                mid[(s + e) / 2].push_back(i);
                flag = false;
            }
        }

        if (flag)
            break;

        SegmentTree Tree(n);
        for (int i = 0; i < k; i++)
        {
            auto [_, s, p] = score[i];
            auto [l, r] = range[s];

            //cout << l << " " << r << " " << p / sz[s] << endl;
            Tree.update(1, 1, n, l, r, p / sz[s]);

            for (auto singer_num : mid[i])
            {
                auto [s, e] = pbs[singer_num];

                ll sum = 0;
                for (auto song : singer[singer_num])
                    sum += Tree.query(1, 1, n, visit[song]);

                if ((double)sum / singer[singer_num].size() <= J)
                    s = i + 1;
                else
                    e = i - 1;

                pbs[singer_num] = {s, e};
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int ans = pbs[singer_of_song[i]].first;
        cout << (ans >= k ? -1 : get<0>(score[ans])) << '\n';
    }
}