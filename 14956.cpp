#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int n, m;

/*
rotate = 0
1 4
2 3
rotate = 1
3 4
2 1
rotate = 2
3 2
4 1
rotate = 3
1 2
4 3
*/
int dr[4][4] = {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 1},
    {0, 0, 1, 1},
};

int dc[4][4] = {
    {0, 0, 1, 1},
    {1, 0, 0, 1},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
};

stack<int> st;

void func(int rotate, int r, int c, int k, int sum)
{
    //cout << rotate << " " << r << " " << c << " " << sum << " -> ";
    if (k == 2)
    {
        cout << c + dc[rotate][sum - 1] << " " << r + dr[rotate][sum - 1] << "\n";
        //cout << r + dr[rotate][sum - 1] << " " << c + dc[rotate][sum - 1] << "\n";
        return;
    }

    int k2 = k / 2;
    int square = (sum - 1) / (k2 * k2);

    if (rotate == 0)
    {
        if (square == 0)
            func(3, r, c, k2, sum - square * k2 * k2);
        else if (square == 1)
            func(0, r + k2, c, k2, sum - square * k2 * k2);
        else if (square == 2)
            func(0, r + k2, c + k2, k2, sum - square * k2 * k2);
        else if (square == 3)
            func(1, r, c + k2, k2, sum - square * k2 * k2);
    }

    else if (rotate == 1)
    {
        if (square == 2)
            func(1, r, c, k2, sum - square * k2 * k2);
        else if (square == 1)
            func(1, r + k2, c, k2, sum - square * k2 * k2);
        else if (square == 0)
            func(2, r + k2, c + k2, k2, sum - square * k2 * k2);
        else if (square == 3)
            func(0, r, c + k2, k2, sum - square * k2 * k2);
    }

    else if (rotate == 2)
    {
        if (square == 2)
            func(2, r, c, k2, sum - square * k2 * k2);
        else if (square == 3)
            func(3, r + k2, c, k2, sum - square * k2 * k2);
        else if (square == 0)
            func(1, r + k2, c + k2, k2, sum - square * k2 * k2);
        else if (square == 1)
            func(2, r, c + k2, k2, sum - square * k2 * k2);
    }
    else if (rotate == 3)
    {
        if (square == 0)
            func(0, r, c, k2, sum - square * k2 * k2);
        else if (square == 3)
            func(2, r + k2, c, k2, sum - square * k2 * k2);
        else if (square == 2)
            func(3, r + k2, c + k2, k2, sum - square * k2 * k2);
        else if (square == 1)
            func(3, r, c + k2, k2, sum - square * k2 * k2);
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    for (int m = 1; m <= 256; m++)
    {
        cout << "m: " << m << "  ->  ";
        func(0, 1, 1, 16, m);
    }
    cout << endl;

    cin >> n >> m;

    if (n == 1)
    {
        cout << "1 1";
        return 0;
    }

    func(0, 1, 1, n, m);
}