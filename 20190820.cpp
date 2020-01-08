#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

char adj[105][105];
int dis[105][105];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> adj[i][j];
        }
    }

    vector<int> st, ans;
    int m;
    cin >> m;

    while (m--)
    {
        int x;
        cin >> x;
        st.push_back(x);
    }

    reverse(st.begin(), st.end());

    while (st.size() >= 3)
    {
        int u = st[st.size() - 1];
        int w = st[st.size() - 2];
        int v = st[st.size() - 3];

        st.pop_back();
        st.pop_back();
        st.pop_back();

        bool flag = false;
        vector<int> temp;
        if (adj[u][v] == '0' && u != v)
        {
            for (int i = 1; i <= n; i++)
            {
                if (adj[u][i] == '1' && adj[i][v] == '1' && i == w)
                    flag = true;
            }
        }

        //cout << "temp size: " << temp.size() << '\n';
        if (flag)
        {
            st.push_back(v);
            st.push_back(u);
        }
        else
        {
            ans.push_back(u);
            st.push_back(v);
            st.push_back(w);
        }
    }

    cout << ans.size() + st.size() << '\n';
    for (auto i : ans)
        cout << i << " ";
    reverse(st.begin(), st.end());
    for (auto i : st)
        cout << i << " ";
}