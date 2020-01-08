#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

const int DELETE = 1;
const int NOT_DELETE = 2;

class Trie
{
private:
    Trie *next[128];

public:
    int finish;
    int cnt;
    Trie()
    {
        finish = false;
        cnt = 0;
        memset(next, 0, sizeof(next));
    }

    ~Trie()
    {
        for (int i = 0; i < 128; i++)
        {
            if (next[i])
                delete next[i];
        }
    }

    void insert(const char *key, int chk)
    {
        if (*key == '\0')
            finish = chk;
        else
        {
            int cur = *key;
            if (!next[cur])
                next[cur] = new Trie();
            next[cur]->insert(key + 1, chk);
        }
    }

    pii get_ans()
    {
        int cnt = (finish == DELETE), m = finish;
        for (int i = 0; i < 128; i++)
        {
            if (next[i])
            {
                auto [a, b] = next[i]->get_ans();

                cnt += b;

                m = max(a, m);
            }
        }

        //cout << x << " " << m << " " << cnt << endl;

        if (m == NOT_DELETE)
            return {NOT_DELETE, cnt};
        else if (m == DELETE)
            return {DELETE, 1};
        else
            return {-1, -INF};
    }
};

char str[25];
int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        Trie trie;
        int n;
        cin >> n;
        while (n--)
        {
            cin >> str;
            trie.insert(str, DELETE);
        }
        cin >> n;
        while (n--)
        {
            cin >> str;
            trie.insert(str, NOT_DELETE);
        }

        auto [a, b] = trie.get_ans();
        cout << b << '\n';
    }
}