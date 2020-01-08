#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 12345678987654321;
const int MOD = 1e9 + 7;
using tt = tuple<int, int, int>;

int n, k, sx, sy, ex, ey;
vector<tt> flower;
ll dp_x[100'005], dp_y[100'005];
int via_x[300'005], via_y[300'005], via[300'005];
int _x[300'005], _y[300'005];

vector<pii> ans;

void f(int i)
{
    if (via[i] != -1)
        f(via[i]);

    ans.push_back({_x[i], _y[i]});
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(via, -1, sizeof(via));
    memset(via_x, -1, sizeof(via_x));
    memset(via_y, -1, sizeof(via_y));

    for (int i = 0; i <= 100'000; i++)
        dp_x[i] = dp_y[i] = -INF;

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        flower.push_back({x, y, z});
        if (i == 0)
            sx = x, sy = y;
        else if (i == n - 1)
            ex = x, ey = y;
    }

    vector<tt> query;

    for (auto [x, y, z] : flower)
        if (sx <= x && x <= ex && sy <= y && y <= ey)
            query.push_back({x, y, z});

    sort(query.begin(), query.end());

    _x[0] = sx;
    _y[0] = sy;
    dp_x[sx] = dp_y[sy] = get<2>(query[0]);
    via_x[sx] = via_y[sy] = 0;

    for (int i = 1; i < query.size() - 1; i++)
    {

        auto [x, y, f] = query[i];
        _x[i] = x;
        _y[i] = y;

        ll pre = max(dp_x[x], dp_y[y]);

        if (pre - k < 0)
            continue;

        via[i] = (dp_x[x] > dp_y[y] ? via_x[x] : via_y[y]);

        ll cur = pre - k + f;
        if (dp_x[x] < cur)
        {
            via_x[x] = i;
            dp_x[x] = cur;
        }

        if (dp_y[y] < cur)
        {
            dp_y[y] = cur;
            via_y[y] = i;
        }
    }

    ll cur = max(dp_x[ex], dp_y[ey]) - k + get<2>(query.back());
    f(((dp_x[ex] > dp_y[ey]) ? via_x[ex] : via_y[ey]));
    ans.push_back({ex, ey});

    cout << cur << "\n";
    cout << ans.size() << "\n";
    for (auto [x, y] : ans)
        cout << x << " " << y << "\n";
}