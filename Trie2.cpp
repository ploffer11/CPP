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
    vector<Trie *> next;
    int my_key;

    Trie *next_trie(int cur)
    {
        for (auto ptr : next)
            if (ptr->my_key == cur)
                return ptr;

        return NULL;
    }

public:
    int cnt;
    Trie(int my_key) : cnt(0), my_key(my_key) {}

    void insert(string &s, int i)
    {
        if (i == s.size())
        {
            cnt++;
            return;
        }

        int cur = s[i] - 'a';
        Trie *ptr = next_trie(cur);

        if (ptr)
            ptr->insert(s, i + 1);
        else
        {
            Trie *new_trie = new Trie(cur);
            next.push_back(new_trie);
            return new_trie->insert(s, i + 1);
        }
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
}