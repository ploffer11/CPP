#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class ExtendedGCD
{
private:
    vector<int> x, y, r, q;

    int gcd(int a, int b)
    {
        return (a % b == 0 ? b : gcd(b, a % b));
    }

public:
    // solve ax + by = c
    pii solve_equation(int a, int b, int c)
    {
        if (c % gcd(a, b) != 0)
            return {INF, INF};

        x = {1, 0};
        y = {0, 1};
        r = {a, b};

        while (1)
        {
            int r2 = r[r.size() - 2];
            int r1 = r[r.size() - 1];
            q.push_back(r2 / r1);
            r.push_back(r2 % r1);

            if (r[r.size() - 1] == 0)
                break;

            int x1 = x[x.size() - 1];
            int x2 = x[x.size() - 2];

            int y1 = y[y.size() - 1];
            int y2 = y[y.size() - 2];

            int q1 = q[q.size() - 1];
            x.push_back(x2 - x1 * q1);
            y.push_back(y2 - y1 * q1);
        }

        int mul = c / gcd(a, b);
        pii ret = {x[x.size() - 1] * mul, y[y.size() - 1] * mul};
        x.clear(), y.clear(), r.clear(), q.clear();
        return ret;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    ExtendedGCD EGCD;

    int a = 16, b = 12, c = 4;
    auto [x, y] = EGCD.solve_equation(a, b, c);
    printf("%dx + %dy = %d\n", a, b, c);
    printf("x = %d, y = %d", x, y);
}