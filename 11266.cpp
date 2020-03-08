#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize ("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int INF = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 10005;

vector<int> adj[MAX];
stack<pii> st;
vector<vector<pii>> bcc;
int num[MAX], deg[MAX];
int cnt;

int dfs(int s, int prev = -1)
{
    int ret = num[s] = ++cnt;

    for (auto e : adj[s])
    {
        if (e == prev)
            continue;

        if (num[s] > num[e])
            st.push({s, e});
        if (num[e] > 0)
            ret = min(ret, num[e]);
        else
        {
            int temp = dfs(e, s);
            ret = min(ret, temp);
            if (temp >= num[s])
            {
                vector<pii> cur;
                while (!st.empty() && st.top() != pii(s, e))
                {
                    cur.push_back(st.top());
                    st.pop();
                }
                cur.push_back(st.top());
                st.pop();
                bcc.push_back(cur);
            }
        }
    }

    return ret;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int v, e;
    cin >> v >> e;

    for (int i = 1; i <= e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= v; i++)
        if (!num[i])
            dfs(i);

    for (auto &vt : bcc)
    {
        vector<int> temp;
        for (auto [x, y] : vt)
        {
            // cout << x << " " << y << "\n";
            temp.push_back(x);
            temp.push_back(y);
        }
        // cout << "end\n";
        sort(temp.begin(), temp.end());
        temp.resize(unique(temp.begin(), temp.end()) - temp.begin());

        for (auto i : temp)
        {
            deg[i]++;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= v; i++)
        if (deg[i] >= 2)
            ans.push_back(i);

    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
}   