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
const int MAX = -1;

class Hungarian
{
private:
    int n, m;
    vector<vector<int>> mat;
    vector<int> matched;
    
public:
    Hungarian(int n, int m) : n(n), m(m), mat(n + 1, vector<int>(m + 1)), matched(n + 1)  {}
    
    void update(int i, int j, int v) 
    {
        mat[i][j] = v;
    }
    
    int hungarian()
    {
        vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1), minv(m + 1);
        vector<char> used(m + 1);
        for (int i = 1; i <= n; ++i) 
        {
            p[0] = i;
            int j0 = 0;
            fill(minv.begin(), minv.end(), INF);
            fill(used.begin(), used.end(), false);
            do 
            {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1;
                for (int j = 1; j <= m; ++j) 
                {
                    if (!used[j]) 
                    {
                        int cur = mat[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta) delta = minv[j], j1 = j;
                    }
                }
                for (int j = 0; j <= m; ++j) 
                {
                    if (used[j])
                        u[p[j]] += delta, v[j] -= delta;
                    else
                        minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            do 
            {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        for (int j = 1; j <= m; ++j) 
            matched[p[j]] = j;
        return -v[0];
    }
};

main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    
    int n;
    cin >> n;
    Hungarian H(n, n);
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1, x; j <= n; j++)
        {
            cin >> x;
            H.update(i, j, x);
        }
    }
    
    cout << H.hungarian();
}