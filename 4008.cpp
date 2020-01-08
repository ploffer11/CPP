#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
const ll INF = (ll)1 << 60;
const int MOD = 1e9 + 7;
const int MAX = 1'000'005;

class ConvexHullTrick
{
private:
    struct Line
    {
        ll s, i;
        Line(ll _s, ll _i) : s(_s), i(_i) {}
    };

    vector<Line> st;

    ld cross_point(Line a, Line b)
    {
        if (a.s == b.s)
            return (a.i > b.i ? INF : -INF);
        return (ld)(a.i - b.i) / (b.s - a.s);
    }

    void push_line(Line ins)
    {
        while (st.size() >= 2 && cross_point(st[st.size() - 2], st.back()) > cross_point(st.back(), ins))
            st.pop_back();

        st.push_back(ins);
    }

public:
    void add_line(ll a, ll b)
    {
        push_line(Line(a, b));
    }

    ll get_max_v1(ll x)
    {
        static ll ptr = 0;

        while (ptr + 1 != st.size() && cross_point(st[ptr], st[ptr + 1]) < x)
            ptr++;

        return x * st[ptr].s + st[ptr].i;
    }

    ll get_max_v2(ll x)
    {
        int s = 0, e = st.size() - 1;
        while (s != e)
        {
            int m = (s + e) / 2 + 1;
            if (cross_point(st[m], st[m - 1]) > x)
                e = m - 1;
            else
                s = m;
        }
        return x * st[s].s + st[s].i;
    }
};

ll n, a, b, c;
ll dp[MAX], s[MAX], x[MAX];

ll f(ll x)
{
    return a * x * x + b * x + c;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    ConvexHullTrick CHT;

    cin >> n >> a >> b >> c;

    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
        s[i] = s[i - 1] + x[i];
    }

    dp[1] = f(x[1]);
    CHT.add_line(-2 * a * s[1], dp[1] + a * s[1] * s[1] - b * s[1]);
    for (int i = 2; i <= n; i++)
    {
        dp[i] = max(f(s[i]), CHT.get_max_v1(s[i]) + f(s[i]));
        CHT.add_line(-2 * a * s[i], dp[i] + a * s[i] * s[i] - b * s[i]);
    }

    cout << dp[n];
}