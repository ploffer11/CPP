#include <bits/stdc++.h>
using namespace std;

int answer;
int A[5005], B[5005], C[5005], dp[5005][5005];

int main(int argc, char **argv)
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T, test_case;

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        answer = 0;

        int n;
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = 0;
            }
            cin >> A[i];
        }

        for (int i = 1; i <= n; i++)
        {
            cin >> B[i];
            C[i] = (A[i] == B[i]);
            answer += C[i];
        }

        for (int i = 1; i <= n - 1; i++)
        {
            int p = C[i] + C[i + 1];
            int q = (A[i] == B[i + 1]) + (A[i + 1] == B[i]);
            dp[i][i + 1] = q - p;
        }

        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i - j <= 0 || i + j >= n + 1)
                    break;

                int p = C[i - j] + C[i + j];
                int q = (A[i + j] == B[i - j]) + (A[i - j] == B[i + j]);
                dp[i - j][i + j] = dp[i - (j - 1)][i + (j - 1)] + q - p;
                //cout << "dp[i-j][i+j]: " << i - j << " " << i + j << endl;
            }

            for (int j = 1; j <= n; j++)
            {
                if (i - j <= 0 || i + j + 1 >= n + 1)
                    break;

                int p = C[i - j] + C[i + j + 1];
                int q = (A[i - j] == B[i + j + 1]) + (A[i + j + 1] == B[i - j]);
                dp[i - j][i + j + 1] = dp[i - (j - 1)][i + j] + q - p;
                //cout << "dp[i-j][i+j+1]: " << i - j << " " << i + j + 1 << endl;
            }
        }

        int m = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                m = max(m, dp[i][j]);
                //cout << dp[i][j] << " ";
            }
            //cout << endl;
        }

        cout << "Case #" << test_case + 1 << endl;
        cout << answer + m << endl;
    }

    return 0;
}