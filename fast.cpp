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

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    FastMinCostMaxFlow MCMF(n);
    MCMF.add_edge(MCMF.source, 1, 2, 0);
    MCMF.add_edge(n, MCMF.sink, 2, 0);
    while (m--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        MCMF.add_edge(u, v, 1, c);
        MCMF.add_edge(v, u, 1, c);
    }

    auto [cost, flow] = MCMF.mcmf();
    cout << cost << endl;
    cout << flow;
}