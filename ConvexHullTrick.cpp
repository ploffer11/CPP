#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = (ll)1 << 60;
const int MOD = 1e9 + 7;
const int MAX = 1'000'005;

using ld = long double;
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

        ptr = (ptr >= st.size() ? st.size() - 1 : ptr);
        while (ptr + 1 != st.size() && cross_point(st[ptr], st[ptr + 1]) < x)
            ptr++;
        return x * st[ptr].s + st[ptr].i;
    }

    ll get_max_v2(ll x)
    {
        int s = 0, e = st.size() - 1;
        while (s <= e)
        {
            int m = (s + e) / 2;
            if (cross_point(st[m], st[m - 1]) > x)
                e = m - 1;
            else
                s = m + 1;
        }
        return x * st[s].s + st[s].i;
    }
};