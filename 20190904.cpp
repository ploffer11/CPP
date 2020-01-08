#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int visit[200005];
bool finish[200005];

vector<int> adj[200005];

int bfs(int s, int want)
{
    memset(visit, 0, sizeof(visit));

    visit[s] = true;
    queue<pii> q;
    q.push({0, s});

    while (!q.empty())
    {
        auto [depth, node] = q.front();
        q.pop();
        if (depth == want)
            return node;

        for (auto e : adj[node])
        {
            if (!visit[e])
            {
                q.push({depth + 1, e});
                visit[e] = true;
            }
        }
    }
}

void add_edge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<tuple<int, int, int>> arr;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;

        arr.push_back({x, 2 * i - 1, 2 * i});
    }

    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());

    for (int i = 0; i < n - 1; i++)
    {
        auto [a, b, c] = arr[i];
        auto [d, e, f] = arr[i + 1];
        cout << b << " " << e << "\n";
        add_edge(b, e);
    }

    for (int i = 0; i < n; i++)
    {
        auto [dis, u, v] = arr[i];
        if (dis == 1)
        {
            cout << u << " " << v << "\n";
            add_edge(u, v);
        }
        else
        {
            int s = i - (dis - 1);
            int e = i + (dis - 1);

            if (e < n)
            {
                cout << v << " " << get<1>(arr[e]) << "\n";
                add_edge(v, get<1>(arr[e]));
            }
            else if (s >= 0)
            {
                cout << v << " " << get<1>(arr[s]) << "\n";
                add_edge(v, get<1>(arr[s]));
            }

            else
            {
                int diff = dis - get<0>(arr[i - 1]);
                if (diff == 0)
                {
                    cout << v << " " << get<2>(arr[i - 1]) << "\n";
                    add_edge(v, get<2>(arr[i - 1]));
                }

                else
                {
                    int k = bfs(u, dis - 1);
                    cout << v << " " << k << "\n";
                    add_edge(v, k);
                }
            }
        }
    }
}