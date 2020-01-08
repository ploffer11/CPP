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

using tt = tuple<int, int, int>;
struct Board
{
    vector<vector<int>> board;
    vector<tt> cube;
    int r, c;

    Board(int r, int c, vector<tt> &cube)
        : board(20, vector<int>(20, 0)), cube(cube), r(r), c(c) {}
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

}