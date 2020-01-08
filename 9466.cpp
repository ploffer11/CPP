#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--)
    {
        int n, ans = 0;
        cin >> n;
        vector<int> to(n + 1), visit(n + 1, 0), start_node(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> to[i];

        int cnt = 1;
        for (int i = 1; i <= n; i++)
        {
            if (!visit[i])
            {
                int j = i;
                for (; !visit[j]; j = to[j])
                {
                    visit[j] = cnt++;
                    start_node[j] = i;
                }

                if (start_node[j] == i)
                    ans += cnt - visit[j];
            }
        }

        cout << n - ans << '\n';
    }
}
