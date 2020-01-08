#include <bits/stdc++.h>
using namespace std;

int ans = 1 << 30;
int n;
vector<vector<int>> board;

int delta(int flag, int idx)
{
    int ret = 0;

    if (flag)
    {
        for (int j = 0; j < n; j++)
            ret += (board[idx][j] == 1 ? -1 : 1);
    }

    else
    {
        for (int i = 0; i < n; i++)
            ret += (board[i][idx] == 1 ? -1 : 1);
    }

    return ret;
}

void change(int flag, int idx)
{
    if (flag)
    {
        for (int j = 0; j < n; j++)
            board[idx][j] = !board[idx][j];
    }

    else
    {
        for (int i = 0; i < n; i++)
            board[i][idx] = !board[i][idx];
    }
}

int main()
{
    int E1 = 0;
    cin >> n;

    board.resize(n);

    for (int i = 0; i < n; i++)
    {
        string inp;
        cin >> inp;
        for (int j = 0; j < n; j++)
        {
            board[i].push_back(inp[j] == 'H' ? 0 : 1);
            E1 += (inp[j] == 'H' ? 0 : 1);
        }
    }

    int epochs = 1000000;
    double k = 10;
    while (epochs--)
    {
        ans = min(ans, E1);

        int flag = rand() % 2;
        int idx = rand() % n;

        int d = delta(flag, idx);
        int E2 = E1 + d;

        if (exp((E1 - E2) / k) > (double)(rand() % 100) / 100)
        {
            change(flag, idx);
            E1 = E2;
        }

        k *= 0.9999;
    }

    cout << ans;
}