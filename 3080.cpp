#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

char str[3005];
ll dp[3005];

ll f(int x)
{
    if (dp[x] != -1)
        return dp[x];

    if (x == 1)
        return dp[1] = 1;

    else
        return dp[x] = ((x * f(x - 1)) % MOD);
}

class Trie
{
private:
    vector<Trie *> next;

public:
    bool finish;
    int cnt;
    int x;

    Trie(int x)
    {
        finish = false;
        cnt = 0;
        this->x = x;
    }

    void insert(const char *key)
    {
        if (*key == '\0')
            finish = true;
        else
        {
            int cur = *key - 'A';

            int i = -1;
            for (int j = 0; j < next.size(); j++)
            {
                if (next[j]->x == cur)
                {
                    i = j;
                    break;
                }
            }

            if (i == -1)
            {
                i = next.size();
                next.push_back(NULL);
                next.back() = new Trie(cur);
                cnt++;
            }

            next[i]->insert(key + 1);
        }
    }

    ll get_ans()
    {
        ll ret = 1;
        for (auto i : next)
        {
            ret *= i->get_ans();
            ret %= MOD;
        }
        return (ret * f(cnt + finish)) % MOD;
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));
    Trie trie(-1);

    vector<string> vt;

    int n;
    cin >> n;
    while (n--)
    {
        cin >> str;
        trie.insert(str);
    }

    cout << trie.get_ans();
}