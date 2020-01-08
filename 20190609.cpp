#include <bits/stdc++.h>
#define N 2800000
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

bool prime[N + 5];
int kth_prime[N + 5], divisor[200005], cnt[N + 5];

void initialize()
{
    memset(prime, 1, sizeof(prime));
    for (int i = 2; i * i <= N; i++)
    {
        if (!prime[i])
            continue;

        for (int j = i; i * j <= N; j++)
            prime[i * j] = 0;
    }

    int cnt = 1;
    for (int i = 2; i <= N; i++)
    {
        if (prime[i])
            kth_prime[i] = cnt++;
    }

    for (int i = 2; i <= 200000; i++)
    {
        if (prime[i])
            continue;
        else
        {
            for (int j = 2; j <= i; j++)
            {
                if (i % j == 0)
                {
                    divisor[i] = i / j;
                    break;
                }
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    initialize();

    int n;
    cin >> n;

    for (int i = 0; i < 2 * n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }


    vector<int> ans;
    for (int i = N; i >= 1; i--)
    {
        while (cnt[i])
        {
            if (prime[i])
            {
                ans.push_back(kth_prime[i]);
                cnt[i]--;
                cnt[kth_prime[i]]--;
            }

            else
            {
                ans.push_back(i);
                cnt[i]--;
                cnt[divisor[i]]--;
            }
        }
    }

    for (auto i : ans)
    {
        cout << i << " ";
    }
}