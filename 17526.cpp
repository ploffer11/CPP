#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int MOD = 1e9 + 7;

const ll INF = 1e18;
class DynamicLichaoTree
{
private:
    class LiChaoTree
    {
    private:
        struct Line
        {
            int idx;
            ll a, b;
            Line(ll a, ll b, int idx = -1) : a(a), b(b), idx(idx) {}

            ll f(ll x)
            {
                return a * x + b;
            }
        };

        struct Node
        {
            int l, r;
            ll xl, xr;
            Line line;
        };

        vector<Node> tree;

    public:
        ll s = -2e12, e = 2e12;
        LiChaoTree()
        {
            tree.push_back({-1, -1, s, e, Line(0, -INF)});
        }

        void add_line(Line new_line, int i = 0)
        {
            ll xl = tree[i].xl, xr = tree[i].xr;
            ll xm = (xl + xr) >> 1;

            Line low = tree[i].line, high = new_line;

            if (low.f(xl) >= high.f(xl))
                swap(low, high);

            if (low.f(xr) <= high.f(xr))
            {
                tree[i].line = high;
                return;
            }

            else if (low.f(xm) <= high.f(xm))
            {
                tree[i].line = high;

                if (tree[i].r == -1)
                {
                    tree[i].r = tree.size();
                    tree.push_back({-1, -1, xm + 1, xr, Line(0, -INF)});
                }
                add_line(low, tree[i].r);
            }
            else
            {
                tree[i].line = low;
                if (tree[i].l == -1)
                {
                    tree[i].l = tree.size();
                    tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
                }
                add_line(high, tree[i].l);
            }
        }

        ll query(ll x, int i = 0)
        {
            if (i == -1)
                return -INF;
            ll xl = tree[i].xl, xr = tree[i].xr;
            ll xm = (xl + xr) >> 1;
            if (x <= xm)
                return max(tree[i].line.f(x), query(x, tree[i].l));
            else
                return max(tree[i].line.f(x), query(x, tree[i].r));
        }

        Line query2(ll x, int i = 0)
        {
            if (i == -1)
                return Line(0, -INF);
            ll xl = tree[i].xl, xr = tree[i].xr;
            ll xm = (xl + xr) >> 1;
            if (x <= xm)
            {
                Line line = query2(x, tree[i].l);
                if (line.f(x) > tree[i].line.f(x))
                    return line;
                else
                    return tree[i].line;
            }
            else
            {
                Line line = query2(x, tree[i].r);
                if (line.f(x) > tree[i].line.f(x))
                    return line;
                else
                    return tree[i].line;
            }
        }
    };

    struct BucketManager
    {
        struct Bucket
        {
            vector<pll> line;
            LiChaoTree *tree;

            Bucket()
            {
                tree = new LiChaoTree();
            }

            void add_line(ll a, ll b)
            {
                line.push_back({a, b});
                tree->add_line({a, b});
            }

            bool delete_line(ll a, ll b)
            {
                bool flag = false;
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == pll(a, b))
                    {
                        line.erase(line.begin() + i);
                        flag = true;
                        break;
                    }
                }

                if (!flag)
                    return false;

                delete tree;
                tree = new LiChaoTree();
                for (auto [a, b] : line)
                    tree->add_line({a, b});

                return true;
            }

            ll query(ll x)
            {
                if (line.empty())
                    return -INF;
                else
                    return tree->query(x);
            }
        };

        vector<Bucket> bucket;
        int bucket_size = 320;
        BucketManager()
        {
            bucket.push_back(Bucket());
        }

        void add_line(ll a, ll b)
        {
            if (bucket.back().line.size() == bucket_size)
                bucket.push_back(Bucket());

            bucket.back().add_line(a, b);
        }

        void delete_line(ll a, ll b)
        {
            for (int i = bucket.size() - 1; i >= 0; i--)
                if (bucket[i].delete_line(a, b))
                    break;
        }

        ll query(ll x)
        {
            ll ret = -INF;
            for (auto &i : bucket)
                ret = max(ret, i.query(x));
            return ret;
        }
    };

    BucketManager BM;

public:
    void add_line(ll a, ll b)
    {
        BM.add_line(a, b);
    }

    // already exist
    void delete_line(ll a, ll b)
    {
        BM.delete_line(a, b);
    }

    ll query(ll x)
    {
        return BM.query(x);
    }
};

ll dp[100005];
ll dis[100005];
ll prepare[100005];
ll pace[100005];
ll sum[100005];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    DynamicLichaoTree LT;

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++)
        cin >> dis[i];

    for (int i = 2; i <= n; i++)
        sum[i] = sum[i - 1] + dis[i];

    for (int i = 1; i <= n - 1; i++)
    {
        cin >> prepare[i] >> pace[i];
    }

    dp[1] = 0;
    LT.add_line(-pace[1], dp[1] - prepare[1] + pace[1] * sum[1]);
    for (int i = 2; i <= n - 1; i++)
    {
        dp[i] = LT.query(sum[i]);
        LT.add_line(-pace[i], dp[i] - prepare[i] + pace[i] * sum[i]);
    }
    cout << -LT.query(sum[n]);
}