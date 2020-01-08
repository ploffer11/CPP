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
    bool finish;
    int cnt;
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
            {
                next[cur] = new Trie();
                cnt++;
            }

            next[cur]->insert(key + 1);
        }
    }

    int find(const char *key)
    {
        if (*key == '\0')
            return 0;

        int cur = *key - 'a';

        if (!finish && cnt == 1)
            return next[cur]->find(key + 1);
        else
            return next[cur]->find(key + 1) + 1;
    }
};

int main()
{
    int n;

    while (cin >> n)
    {
        Trie trie;
        trie.finish = true;
        vector<string> vt;

        for (int i = 0; i < n; i++)
        {
            string inp;
            cin >> inp;
            trie.insert(inp.c_str());
            vt.push_back(inp);
        }

        int type = 0;

        for (auto &str : vt)
        {
            type += trie.find(str.c_str());
        }
        printf("%.2f\n", (double)type / n);
    }
}