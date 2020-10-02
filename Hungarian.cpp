class Hungarian
{
private:
    int r, c;
    vector<vector<int>> mat;
    vector<int> matched;
public:
    Hungarian(int r, int c) : r(r), c(c), mat(r + 1, vector<int>(c + 1)), matched(r + 1)  {}
    
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