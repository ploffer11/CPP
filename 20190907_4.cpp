#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
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

    void insert(const char *key)
    {
        if (*key == '\0')
            finish = true;
        else
        {
            int cur = *key - 'a';
            if (!next[cur])
                next[cur] = new Trie();

            next[cur]->cnt++;
            next[cur]->insert(key + 1);
        }
    }

    int find(const char *key)
    {
        if (*key == '?')
            return this->cnt;

        int cur = *key - 'a';

        if (!next[cur])
            return 0;

        return next[cur]->find(key + 1);
    }
};

Trie prefix_trie[10005];
Trie suffix_trie[10005];

char str[10005];

vector<int> solution(vector<string> words, vector<string> queries)
{
    vector<int> vt;
    /* 
    words = {"frodo",
             "front",
             "frost",
             "frozen",
             "frame",
             "kakao"};
    */

    for (auto &word : words)
    {
        prefix_trie[word.size()].cnt++;

        prefix_trie[word.size()].insert(word.c_str());
        reverse(word.begin(), word.end());
        suffix_trie[word.size()].insert(word.c_str());
    }

    for (auto &query : queries)
    {
        if (query.back() == '?')
            vt.push_back(prefix_trie[query.size()].find(query.c_str()));
        else
        {
            reverse(query.begin(), query.end());
            vt.push_back(suffix_trie[query.size()].find(query.c_str()));
        }
    }

    return vt;
}