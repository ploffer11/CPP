#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> tree(n + 1, INF);

    int k, p;
    cin >> k >> p;

    tree[p] = k;
    int small = k - 1;
    int big = k + 1;

    int i = p / 2;
    while (i >= 1)
    {
        tree[i] = small--;
        i /= 2;
    }

    queue<int> q;       
    q.push(p * 2);
    q.push(p * 2 + 1);

    while (!q.empty())
    {
        int i = q.front();
        q.pop();

        if (i <= n)
        {
            tree[i] = big++;
            q.push(i * 2);
            q.push(i * 2 + 1);
        }
    }

    if (small < 0 || big > n + 1)
    {
        cout << "-1";
        return 0;
    }

    for (int i = 1; i <= small; i++)
        q.push(i);
    for (int i = big; i <= n; i++)
        q.push(i);

    for (int i = 1; i <= n; i++)
    {
        if (tree[i] == INF)
        {
            int s = q.front();
            q.pop();

            int j = i;
            tree[j] = s;
            while (j / 2 >= 1 && tree[j / 2] > tree[j])
            {
                swap(tree[j / 2], tree[j]);
                j /= 2;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << tree[i] << "\n";
}