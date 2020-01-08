#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef tuple<int, int, int> t;
const int INF = 0x3f3f3f3f;

typedef long double ld;
struct ConvexHullTrick
{
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

    void add_line(ll a, ll b)
    {
        push_line(Line(a, b));
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

ll dp[100005];
ll dis[100005];
ll prepare[100005];
ll pace[100005];
ll sum[100005];

int main()
{
    ConvexHullTrick CHT;

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

    // dp[i] = MIN dp[j] + pace[j] * (sum[i] - sum[j]) + prepare[j]
    // dp[i] = MIN dp[j] + pace[j]sum[i] - pace[j]sum[j] + prepare[j]
    // dp[i] = MIN dp[j] + prepare[j] - pace[j]sum[j] + pace[j]sum[i]
    // dp[i] = MAX -dp[j] - prepare[j] + pace[j]sum[j] - pace[j]sum[i]
    dp[1] = 0;
    CHT.add_line(-pace[1], -dp[1] - prepare[1] + pace[1] * sum[1]);
    for (int i = 2; i <= n - 1; i++)
    {
        dp[i] = CHT.get_max_v2(sum[i]);
        cout << dp[i] << " <-\n";
        CHT.add_line(-pace[i], dp[i] - prepare[i] + pace[i] * sum[i]);
    }
    cout << CHT.get_max_v2(sum[n]);
}