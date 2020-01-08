#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int cnt;
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

    int n, m;
    cin >> m >> n;
    while (m--)
    {
        int a, b;
        cin >> a >> b;

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

        int c = ++cnt;
        for (auto i : temp)
            scc[i] = c;

        temp.clear();
    }

    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        //cout << scc[i] << " " << scc[i + n] << '\n';
        if (scc[i] == scc[i + n])
            flag = false;
    }

    cout << (flag ? "^_^" : "OTL");
}