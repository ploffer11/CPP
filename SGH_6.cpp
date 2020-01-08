#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using Matrix = vector<vector<ll>>;
Matrix matmul(Matrix A, Matrix B)
{
    int a = A.size();
    int b = A[0].size();
    int c = B[0].size();

    Matrix ret;
    ret.resize(a, vector<ll>(c, 0));

    for (int i = 0; i < a; i++)
        for (int j = 0; j < c; j++)
            for (int k = 0; k < b; k++)
            {
                ret[i][j] += A[i][k] * B[k][j];
                ret[i][j] %= MOD;
            }
    return ret;
}

Matrix matpow(Matrix A, int m)
{
    if (m == 1)
        return A;

    Matrix B = matpow(A, m / 2);
    if (m % 2 == 0)
        return matmul(B, B);
    else
        return matmul(A, matmul(B, B));
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t, n, d;
    cin >> t >> n >> d;

    vector<Matrix> vt;

    vt.resize(t);
    for (int i = 0; i < t; i++)
    {
        vt[i] = Matrix(n, vector<ll>(n, 0));

        int q;
        cin >> q;
        while (q--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            vt[i][a - 1][b - 1] = c;
        }
    }

    Matrix ALL = vt[0];
    for (int i = 1; i < t; i++)
        ALL = matmul(ALL, vt[i]);

    ll power = d / t;
    ll extra = d % t;

    Matrix I = Matrix(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        I[i][i] = 1;

    if (power != 0)
        I = matmul(I, matpow(ALL, power));

    for (int i = 0; i < extra; i++)
        I = matmul(I, vt[i]);

    for (auto &i : I)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << "\n";
    }
}