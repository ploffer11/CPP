#include <bits/stdc++.h>
using namespace std;

int p[1000];

int find(int me)
{
    return (p[me] < 0 ? (me) : (p[me] = find(p[me])));
}

void uni(int a, int b)
{
    a = find(a), b = find(b);
    if (a != b)
    {
        p[a] += p[b];
        p[b] = a;
    }
}

int main()
{
    memset(p, -1, sizeof(p));

    int k, n, f;
    cin >> k >> n >> f;
    while (f--)
    {
        int a, b;
        cin >> a >> b;
        uni(a, b);
    }

    int save = -1;

    for (int i = 1; i <= n; i++)
    {
        if (p[i] == -k)
        {
            save = i;
            break;
        }
    }

    if (save == -1)
        cout << -1;

    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (find(i) == save)
            {
                cout << i << " ";
            }
        }
    }
}