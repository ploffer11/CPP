#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

int in[200], out[200];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        int n, m;
        cin >> n >> m;
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            in[v]++;
            out[u]++;
        }

        int I = 0, O = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!in[i])
                I++;
            if (!out[i])
                O++;
        }

        cout << max(I, O) << '\n';
    }
}
