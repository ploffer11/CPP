#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

map<pii, int> mp;

int f(int n)
{
    int cnt = 0;
    while (n)
    {
        cnt++;
        n /= 10;
    }

    return cnt;
}

int main()
{
    int n = 0;
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    int i = 0, j = 0;

    int cnt = 1;
    int cnt2 = 0, cnt3 = 1, cnt4 = 0, cnt5 = 0;

    int dr[] = {0, -1, 0, 1};
    int dc[] = {1, 0, -1, 0};

    while (abs(i) <= 5500 && abs(j) <= 5500)
    {

        if (r1 <= i && i <= r2 && c1 <= j && j <= c2)
        {
            mp[{i, j}] = cnt;
            n = max(n, f(cnt));
        }

        i += dr[cnt2 % 4];
        j += dc[cnt2 % 4];

        cnt4++;
        cnt++;

        if (cnt3 == cnt4 && !cnt5)
        {
            cnt4 = 0;
            cnt5 = 1;
            cnt2++;
        }

        else if (cnt3 == cnt4)
        {
            cnt5 = 0;
            cnt4 = 0;
            cnt2++;
            cnt3++;
        }
    }

    for (int i = r1; i <= r2; i++)
    {
        for (int j = c1; j <= c2; j++)
        {
            cout.width(n);
            cout << right << mp[{i, j}] << " ";
        }
        cout << endl;
    }
}