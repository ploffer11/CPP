#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

using ld = long double;
class ConvexHullTrick
{
private:
    int ptr = 0;
    struct Line
    {
        ll a, b;
        int idx;
        Line(ll a, ll b, int idx) : a(a), b(b), idx(idx) {}
        ll f(ll x) { return a * x + b; }
    };

    deque<Line> dq;

    ld cross_point(Line x, Line y)
    {
        if (x.a == y.a)
            return (x.b > y.b ? INF : -INF);
        return (ld)(x.b - y.b) / (y.a - x.a);
    }

    void add_line(Line ins)
    {
        while (dq.size() >= 2 && cross_point(dq[dq.size() - 2], dq.back()) > cross_point(dq.back(), ins))
            dq.pop_back();

        dq.push_back(ins);
    }

public:
    void add_line(ll a, ll b, int idx)
    {
        add_line(Line(a, b, idx));
    }

    ll query1(ll x)
    {
        while (ptr + 1 != dq.size() && cross_point(dq[ptr], dq[ptr + 1]) <= x)
            dq.pop_front();
        return dq[ptr].f(x);
    }

    Line query2(ll x)
    {
        while (ptr + 1 != dq.size() && cross_point(dq[ptr], dq[ptr + 1]) <= x)
            dq.pop_front();
        return dq[ptr];
    }
};

ll dp[100005][2], psum[100005], arr[100005];
int via[100005][201];
vector<int> ans;
void track(int i, int j)
{
    if (j == 0)
        return;

    track(via[i][j], j - 1);
    ans.push_back(via[i][j]);
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        psum[i] = psum[i - 1] + arr[i];
    }

    for (int j = 1; j <= k; j++)
    {
        ConvexHullTrick CHT;

        CHT.add_line(psum[j], -psum[j] * psum[j] + dp[j][(j - 1) % 2], j);

        for (int i = j + 1; i <= n; i++)
        {
            // auto x = CHT.query(psum[i]);
            // dp[i][j % 2] = x.s * psum[i] + x.i;
            // via[i][j] = x.idx;
            CHT.add_line(psum[i], -psum[i] * psum[i] + dp[i][(j - 1) % 2], i);
        }
    }

    cout << dp[n][k % 2] << "\n";
    track(n, k);
    for (auto i : ans)
        cout << i << " ";
}