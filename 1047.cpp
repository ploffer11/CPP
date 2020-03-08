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

using tt = tuple<int, int, int>;

vector<tt> point;
vector<int> x, y;
main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    int ans = n;

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int X, Y, Z;
        cin >> X >> Y >> Z;
        point.push_back({X, Y, Z});
        x.push_back(X);
        y.push_back(Y);
        sum += Z;
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                for (int l = k; l < n; l++)
                {
                    int x_min = x[i], x_max = x[j];
                    int y_min = y[k], y_max = y[l];

                    int sum_in = 0, cnt = 0;
                    vector<int> temp;
                    for (auto [X, Y, Z] : point)
                    {
                        if (x_min <= X && X <= x_max && y_min <= Y && Y <= y_max)
                        {
                            temp.push_back(Z);
                            sum_in += Z;
                            cnt++;
                        }
                    }
                    int demand = (x_max - x_min) * 2 + (y_max - y_min) * 2;

                    sort(temp.begin(), temp.end());
                    while ((sum - sum_in) < demand && !temp.empty())
                    {
                        sum_in -= temp.back();
                        temp.pop_back();
                        cnt--;
                    }

                    if (sum - sum_in >= demand)
                        ans = min(ans, n - cnt);
                }
            }
        }
    }

    cout << ans;
}