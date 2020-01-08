#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> pdd;

vector<int> adj[105];
vector<pdd> mouse, home;
int n, m, s, v;
int visit[105], match[105];

bool dfs(int s)
{
    visit[s] = 1;

    for (auto e : adj[s])
    {
        if (match[e] == -1 || (!visit[match[e]] && dfs(match[e])))
        {
            match[e] = s;
            return true;
        }
    }

    return false;
}

int main()
{
    cin >> n >> m >> s >> v;

    for (int i = 1; i <= n + m; i++)
    {
        double a, b;
        cin >> a >> b;
        (i <= n ? mouse : home).push_back({a, b});
    }

    int cnt = 0;
    for (auto [x1, y1] : mouse)
    {
        int cnt2 = 0;
        for (auto [x2, y2] : home)
        {
            auto d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

            if (d <= s * s * v * v)
                adj[cnt].push_back(cnt2);

            cnt2++;
        }
        cnt++;
    }

    memset(match, -1, sizeof(match));

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        memset(visit, 0, sizeof(visit));
        if (dfs(i))
            ans++;
    }

    cout << n - ans;
}