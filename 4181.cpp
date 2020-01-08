#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using ld = long double;
using pld = pair<ld, ll>;
using pll = pair<ll, ll>;

class CCW
{
public:
    int ccw(pii a, pii b, pii c)
    {
        int op = a.first * b.second + b.first * c.second + c.first * a.second;
        op -= (a.second * b.first + b.second * c.first + c.second * a.first);
        if (op > 0)
            return 1;
        else if (op == 0)
            return 0;
        else
            return -1;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    CCW ccw;

    int n;
    cin >> n;

    vector<pii> points;
    while (n--)
    {
        int x, y;
        char z;
        cin >> x >> y >> z;

        if (z == 'Y')
            points.push_back({x, y});
    }

    sort(points.begin(), points.end());

    vector<pii> st;
    st.push_back(points[0]);

    for (int i = 1; i < points.size(); i++)
    {
        while (st.size() >= 2)
        {
            auto &a = st[st.size() - 2];
            auto &b = st.back();
            auto op = ccw.ccw(a, b, points[i]);
            if (op >= 0)
            {
                //if (op == 0)
                //    st.pop_back();
                break;
            }
            else
                st.pop_back();
        }
        st.push_back(points[i]);
    }

    sort(points.begin(), points.end(), [](pii &a, pii &b) { return pii(-a.first, -a.second) < pii(-b.first, -b.second); });
    vector<pii> save = st;
    st.clear();

    for (int i = 0; i < points.size(); i++)
    {
        while (st.size() >= 2)
        {
            auto &a = st[st.size() - 2];
            auto &b = st.back();
            auto op = ccw.ccw(a, b, points[i]);
            if (op >= 0)
            {
                //if (op == 0)
                //    st.pop_back();
                break;
            }
            else
                st.pop_back();
        }
        st.push_back(points[i]);
    }

    if (st.back() == save[0])
        st.pop_back();
    if (save.back() == st[0])
        save.pop_back();

    cout << st.size() + save.size() << '\n';
    for (auto [x, y] : save)
        cout << x << " " << y << "\n";
    for (auto [x, y] : st)
        cout << x << " " << y << "\n";
}