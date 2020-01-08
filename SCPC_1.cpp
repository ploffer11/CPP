#include <bits/stdc++.h>
using namespace std;
const int MAX = 30000;

int answer;
int prime[30050];

void era()
{
    for (int i = 2; i <= MAX; i++)
        prime[i] = 1;

    for (int i = 2; i * i <= MAX; i++)
    {
        if (!prime[i])
            continue;

        for (int j = i; i * j <= MAX; j++)
            prime[i * j] = 0;
    }

    prime[1] = 0;
}

int bfs(string n)
{
    typedef pair<string, int> psi;
    queue<psi> q;

    if (prime[stoi(n)])
        q.push(psi(n, 1));

    int ret = 0;
    while (!q.empty())
    {
        auto str = q.front().first;
        auto cnt = q.front().second;
        q.pop();
        ret = max(ret, cnt);

        if (str.size() == 1)
        {
            ret = max(ret, cnt);
            continue;
        }
        for (int i = 0; i < str.size(); i++)
        {
            string new_str = str.substr(0, i) + str.substr(i + 1, n.size());
            //cout << new_str << endl;
            if (prime[stoi(new_str)])
            {
                q.push(psi(new_str, cnt + 1));
            }
        }
    }
    return ret;
}

int main(int argc, char **argv)
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    era();

    int T, test_case;

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        string a, b;
        cin >> a >> b;

        int A = bfs(a);
        int B = bfs(b);

        if (A == B)
            answer = 3;
        else if (A > B)
            answer = 1;
        else
            answer = 2;

        cout << "Case #" << test_case + 1 << endl;
        cout << answer << endl;
    }

    return 0;
}