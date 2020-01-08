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
const int MAX = 520;

vector<int> chain;
bool visit[MAX];
int check[MAX][MAX];
int cnt[MAX];
vector<int> adj[MAX];
bool flag = false;

void back_tracking(int max_depth, int depth, int s, int n)
{
    if (flag)
        return;

    if (depth == max_depth)
    {
        bool flag2 = true;
        for (int i = 0; i < depth; i++)
        {
            for (int j = i + 1; j < depth; j++)
            {
                if (!check[chain[i]][chain[j]])
                {
                    flag2 = false;
                    break;
                }
            }
        }

        if (flag2)
            flag = true;

        return;
    }

    for (auto i : adj[s])
    {
        if (!visit[i] && cnt[i] >= max_depth - depth - 1)
        {
            bool flag2 = true;
            for (int j = 0; j < depth; j++)
                if (!check[chain[j]][i])
                    flag2 = false;
            if (!flag2)
                continue;

            chain.push_back(i);
            visit[i] = true;

            back_tracking(max_depth, depth + 1, i, n);

            if (flag)
                return;

            visit[i] = false;
            chain.pop_back();
        }
    }
}

void solve(int n)
{
    flag = false;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char x;
            cin >> x;
            if (x == 'W')
            {
                check[i][j] = 1;
                adj[i].push_back(j);
                cnt[i]++;
            }
        }
    }

    int k = 1 + (int)log2(n);
    for (int i = n; i >= 1; i--)
    {
        if (cnt[i] < k - 1)
            continue;

        chain.push_back(i);
        visit[i] = true;

        back_tracking(k, 1, i, n);

        if (flag)
            break;
        visit[i] = false;
        chain.pop_back();
    }

    for (auto i : chain)
        cout << i << " ";
    cout << "\n";

    for (int i = 1; i <= n; i++)
    {
        adj[i].clear();
        visit[i] = false;
        cnt[i] = 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            check[i][j] = 0;

    chain.clear();
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        solve(n);
    }
}