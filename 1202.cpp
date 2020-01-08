#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
const int MAX = 1'000'005;

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

string s;
int board[11][MAX];
int ans[10][10];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    ExtendedGCD EGCD;

    cin >> s;

    for (int i = 1; i < s.size(); i++)
    {
        int j = (s[i] - s[i - 1] >= 0) ? s[i] - s[i - 1] : s[i] - s[i - 1] + 10;
        for (int k = 0; k <= 10; k++)
        {
            board[k][i] = k * 10 + j;
            cout << board[k][i] << " ";
        }
        cout << endl;
    }

    cout << "?" << endl;

    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << "-1 ";
                continue;
            }

            else if (i == 0 || j == 0)
            {
                int temp = max(i, j);
                ll save = 0;
                for (int k = 1; k < s.size(); k++)
                {
                    int m = INF;
                    for (int l = 0; l <= 10; l++)
                    {
                        if (board[l][k] % temp == 0)
                            m = min(m, board[l][k] / temp);
                    }
                    save += m;
                }
                cout << (save >= INF ? -1 : save - s.size() + 1) << " ";
                continue;
            }
            
        }
        cout << endl;
    }
}