#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int scc[20005];
bool visit[20005];
vector<int> adj[20005], rev_adj[20005];
vector<int> temp, st;

void dfs(int s, bool flag)
{
    visit[s] = true;

    for (auto e : (flag ? adj[s] : rev_adj[s]))
        if (!visit[e])
            dfs(e, flag);

    (flag ? st : temp).push_back(s);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    for (int test = 1; test <= t; test++)
    {
        int cnt = 0;
        memset(visit, 0, sizeof(visit));
        memset(scc, 0, sizeof(scc));

        int n, m;
        cin >> n >> m;
        while (m--)
        {
            int a, b, c, d;
            cin >> c >> d;

            a = c, b = d;
            //cout << a << " v " << b << '\n';
            adj[(a < 0 ? -a : a + n)].push_back((b < 0 ? -b + n : b));
            adj[(b < 0 ? -b : b + n)].push_back((a < 0 ? -a + n : a));

            rev_adj[(b < 0 ? -b + n : b)].push_back((a < 0 ? -a : a + n));
            rev_adj[(a < 0 ? -a + n : a)].push_back((b < 0 ? -b : b + n));

            a = -c, b = -d;
            //cout << a << " v " << b << '\n';
            adj[(a < 0 ? -a : a + n)].push_back((b < 0 ? -b + n : b));
            adj[(b < 0 ? -b : b + n)].push_back((a < 0 ? -a + n : a));

            rev_adj[(b < 0 ? -b + n : b)].push_back((a < 0 ? -a : a + n));
            rev_adj[(a < 0 ? -a + n : a)].push_back((b < 0 ? -b : b + n));
        }

        for (int i = 1; i <= 2 * n; i++)
        {
            sort(adj[i].begin(), adj[i].end());
            sort(rev_adj[i].begin(), rev_adj[i].end());
        }

        for (int i = 1; i <= 2 * n; i++)
        {
            if (!visit[i])
                dfs(i, true);
        }

        memset(visit, 0, sizeof(visit));
        while (!st.empty())
        {
            int s = st.back();
            st.pop_back();

            if (!visit[s])
                dfs(s, false);

            if (!temp.empty())
            {
                int c = ++cnt;
                for (auto i : temp)
                    scc[i] = c;
            }

            temp.clear();
        }

        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            //cout << scc[i] << " <-> " << scc[i + n] << '\n';
            if (scc[i] == scc[i + n])
                flag = false;
        }

        cout << "Scenario #" << test << ":\n";
        cout << (flag ? "No suspicious bugs found!\n" : "Suspicious bugs found!\n");
        if (test != t)
            cout << "\n";

        for (int i = 1; i <= 2 * n; i++)
        {
            adj[i].clear();
            rev_adj[i].clear();
        }
    }
}