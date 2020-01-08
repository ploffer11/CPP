#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

class Trie
{
private:
    Trie *next[26];

public:
    int cnt, d;
    Trie() : cnt(0)
    {
        memset(next, 0, sizeof(next));
    }

    ~Trie()
    {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }

    void insert(const char *key)
    {
        if (*key == '\0')
            return;

        int cur = *key - 'a';

        if (!next[cur])
            next[cur] = new Trie();

        next[cur]->cnt++;
        next[cur]->insert(key + 1);
    }

    int find(const char *key, int depth)
    {
        if (!depth)
            return cnt;

        int cur = *key - 'a';

        if (!next[cur])
            return 0;

        return next[cur]->find(key + 1, depth - 1);
    }
};

char str[200005];
ll dp[200005];
Trie trie;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    while (n--)
    {
        cin >> str;
        trie.insert(str);
    }

    cin >> str;
    int m = strlen(str);

    for (int i = 0; i < m; i++)
    {
        for (int j = 1; i + j - 1 < m && j <= 300; j++)
        {
            int cnt = trie.find(str + i, j);

            //cout << cnt << " " << i << " " << j << endl;
            if (cnt)
            {
                dp[i + j - 1] += cnt * (i == 0 ? 1 : dp[i - 1]);
                dp[i + j - 1] %= MOD;
            }
            else
                break;
        }
    }

    cout << dp[m - 1];
}