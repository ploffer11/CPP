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

public:
    int cnt;
    char num;
    Trie(char n)
    {
        num = n;
        cnt = 0;
    }

    int index(const char key)
    {
        for (int i = 0; i < next.size(); i++)
            if (next[i]->num == key)
                return i;
        return -1;
    }

    void insert(const char *key)
    {

        int cur = index(*key);
        if (cur == -1)
        {
            cur = next.size();
            next.push_back(new Trie(*key));
        }

        if (*key == '\0')
        {
            next[cur]->cnt++;
            return;
        }
        else
        {
            next[cur]->cnt++;
            next[cur]->insert(key + 1);
        }
    }

    int find(const char *key)
    {
        int ret = 0;
        for (auto i : next)
            ret += i->cnt;

        if (*key == '\0')
            return ret;

        int cur = index(*key);
        return (cur != -1 ? ret + next[cur]->find(key + 1) : ret);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    Trie trie(-1);

    int n, q;
    cin >> n;
    vector<string> arr(n);
    map<string, int> mp;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        mp[arr[i]] = i;
    }

    vector<tuple<int, string, int>> query;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        string inp;
        cin >> inp;
        if (mp.find(inp) == mp.end())
            query.push_back({n - 1, inp, i});
        else
            query.push_back({mp[inp], inp, i});
    }

    sort(query.begin(), query.end());

    int prev = -1;
    vector<int> ans(q);
    for (auto [x, y, z] : query)
    {
        for (int i = prev + 1; i <= x; i++)
        {
            trie.insert(arr[i].c_str());
        }

        ans[z] = trie.find(y.c_str());

        prev = x;
    }

    for (auto i : ans)
        cout << i << "\n";
}