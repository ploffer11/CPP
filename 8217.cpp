#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class FenwickTree
{
private:
    int n;
    vector<ll> tree;

public:
    FenwickTree(int n) : n(n)
    {
        tree.resize(n + 1, 0);
    }

    void update(int i, int diff)
    {
        while (i <= n)
        {
            tree[i] += diff;
            i += -i & i;
        }
    }

    ll query(int i)
    {
        ll ret = 0;
        while (i >= 1)
        {
            ret += tree[i];
            i -= -i & i;
        }
        return ret;
    }
};

const int MAX = 300'005;

vector<int> area_of_city[MAX];
vector<int> mid[MAX];

int s[MAX], e[MAX], ans[MAX];
ll goal[MAX];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        area_of_city[x].push_back(i);
    }

    for (int i = 1; i <= n; i++)
        cin >> goal[i];

    int q;
    cin >> q;
    vector<tuple<int, int, int>> meteor(q + 1);

    for (int i = 1; i <= q; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        meteor[i] = {l, r, x};
    }

    for (int i = 1; i <= n; i++)
    {
        s[i] = 1;
        e[i] = q;
    }

    while (1)
    {
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] <= e[i])
            {
                flag = false;
                mid[(s[i] + e[i]) / 2].push_back(i);
            }
        }
        if (flag)
            break;

        FenwickTree Tree(m + 1);

        for (int i = 1; i <= q; i++)
        {
            auto [l, r, x] = meteor[i];

            if (l <= r)
            {
                Tree.update(l, x);
                Tree.update(r + 1, -x);
            }
            else
            {
                Tree.update(l, x);
                Tree.update(1, x);
                Tree.update(r + 1, -x);
            }

            for (auto city : mid[i])
            {
                ll sum = 0;

                for (auto k : area_of_city[city])
                {
                    sum += Tree.query(k);
                    if (sum >= goal[city])
                        break;
                }

                //cout << i << " " << city << " <-> " << sum << '\n';
                if (sum >= goal[city])
                    e[city] = (s[city] + e[city]) / 2 - 1;
                else
                    s[city] = (s[city] + e[city]) / 2 + 1;
            }
            mid[i].clear();
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (s[i] > q)
            cout << "NIE\n";
        else
            cout << s[i] << "\n";
    }
}