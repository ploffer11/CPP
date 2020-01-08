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
    bool finish;
    Trie *next[10];

public:
    Trie()
    {
        finish = false;
        memset(next, 0, sizeof(next));
    }

    ~Trie()
    {
        for (int i = 0; i < 10; i++)
        {
            if (next[i])
                delete next[i];
        }
    }

    void insert(const char *key)
    {
        if (key[0] == '\0')
            finish = true;

        else
        {
            int cur = key[0] - '0';
            if (!next[cur])
                next[cur] = new Trie();
            next[cur]->insert(key + 1);
        }
    }

    bool find(const char *key)
    {
        if (key[0] == '\0')
            return true;

        else if (finish)
            return false;

        int cur = key[0] - '0';
        return next[cur]->find(key + 1);
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, t;
    cin >> t;
    while (t--)
    {
        bool flag = true;
        Trie trie;
        cin >> n;
        vector<string> vt;
        for (int i = 0; i < n; i++)
        {
            string inp;
            cin >> inp;
            vt.push_back(inp);
        }

        for (auto &str : vt)
            trie.insert(str.c_str());

        for (auto &str : vt)
            if (!trie.find(str.c_str()))
                flag = false;

        cout << (flag ? "YES\n" : "NO\n");
    }
}