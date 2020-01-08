
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using Matrix = vector<vector<ll>>;

Matrix matmake(int r, int c)
{
    return Matrix(r, vector<ll>(c, 0));
}

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