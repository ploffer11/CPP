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
    bool finish, cnt;
    Trie()
    {
        finish = false;
        cnt = 0;
        memset(next, 0, sizeof(next));
    }

    ~Trie()
    {
        for (int i = 0; i < 26; i++)
        {
            if (next[i])
                delete next[i];
        }
    }

    void insert(const char *key)
    {
        if (*key == '\0')
            finish = true;
        else
        {
            int cur = *key - 'a';
            if (!next[cur])
                next[cur] = new Trie();

            next[cur]->insert(key + 1);
        }
    }

    Trie *find(const char *key)
    {
        if (*key == '\0')
            return this;

        int cur = *key - 'a';

        if (!next[cur])
            return NULL;

        return next[cur]->find(key + 1);
    }
};