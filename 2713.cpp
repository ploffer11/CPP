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

int arr[25][25];

string binary(int n)
{
    string ret = "";

    while (n)
    {
        ret += '0' + (n % 2 == 1);
        n /= 2;
    }

    int cnt = ret.size();
    for (int i = 0; i < 5 - cnt; i++)
        ret += '0';

    reverse(ret.begin(), ret.end());

    return ret;
}

bool valid(int i, int j, int r, int c)
{
    return (1 <= i && i <= r && 1 <= j && j <= c);
}

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
int ddir[] = {1, 2, 3, 0};

void fill(int r, int c, string t)
{
    memset(arr, -1, sizeof(arr));

    int R = 1, C = 0, cnt = 0, dir = 0;

    while (cnt < t.size())
    {
        int i = R + dr[dir], j = C + dc[dir];
        if (valid(i, j, r, c) && arr[i][j] == -1)
        {
            arr[i][j] = t[cnt++] - '0';
        }
        else
        {
            dir = ddir[dir];
            i = R + dr[dir], j = C + dc[dir];
            arr[i][j] = t[cnt++] - '0';
        }
        //cout << i << " " << j << " " << cnt - 1 << " " << t[cnt - 1] << "\n";
        R = i, C = j;
    }
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    //cout << binary(1) << endl;
    int t;
    cin >> t;
    while (t--)
    {
        int r, c;
        string s, t;
        cin >> r >> c;
        getline(cin, s);

        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == ' ')
                t += "00000";
            else
                t += binary(s[i] - 'A' + 1);
        }
        //cout << "t: " << t << "\n";
        fill(r, c, t);

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                cout << (arr[i][j] == -1 ? 0 : arr[i][j]);
        cout << "\n";
    }
}