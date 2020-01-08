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
    class LinkedList
    {
    public:
        Trie *ptr;
        LinkedList *next;
        LinkedList(Trie *ptr) : ptr(ptr), next(NULL) {}
        ~LinkedList()
        {
            delete ptr;
            delete next;
        }

        // 첫글자가 겹치는 트라이의 포인터를 반환
        Trie *find(char key)
        {
            if (ptr->key[0] == key)
                return ptr;
            return (next ? next->find(key) : NULL);
        }

        // 새로운 트라이 포인터를 링크드 리스트에 추가
        void push_back(Trie *new_ptr)
        {
            if (next)
                next->push_back(new_ptr);
            else
                next = new LinkedList(new_ptr);
        }
    };

    LinkedList *next;

    // 첫글자가 겹치는 트라이의 포인터를 반환
    Trie *next_trie(char cur)
    {
        return (next ? next->find(cur) : NULL);
    }

public:
    int cnt;
    string key;

    Trie(string key) : cnt(0), key(key), next(NULL) {}
    ~Trie()
    {
        delete next;
    }

    void insert(string &s, int i)
    {
        if (i == s.size())
        {
            cnt++;
            return;
        }

        Trie *ptr = next_trie(s[i]);

        if (ptr)
        {
            // [0, i) 구간이 겹침
            int j = 0;
            for (; j < ptr->key.size() && i + j < s.size(); j++)
            {
                if (s[i + j] != ptr->key[j])
                {
                    break;
                }
            }

            if (j == ptr->key.size())
            {
                ptr->insert(s, i + j);
                return;
            }

            // ptr->key abcd 인 상태, 새로 들어온건 abc

            // d 스트링 만들기
            string new_string = ptr->key.substr(j);

            // abcd 를 abc로 변경
            ptr->key = ptr->key.substr(0, j);

            // 현재 next를 보관
            LinkedList *temp = ptr->next;

            // d 를 가지는 trie 만듬
            Trie *new_trie = new Trie(new_string);

            // 그 트라이의 next를 temp로 변경
            new_trie->next = temp;
            new_trie->cnt = ptr->cnt;

            // ptr의 next는 새로운 링크드리스트를 만들고 d 트라이로 이음
            ptr->next = new LinkedList(new_trie);

            //  ""를 가지는 새로운 trie 만들어 cnt 올리고 푸시
            if (i + j == s.size())
                ptr->next->ptr->cnt++;

            else
            {
                new_trie = new Trie(s.substr(i + j));
                new_trie->cnt++;
                ptr->next->push_back(new_trie);
            }

            ptr->cnt = 0;
        }
        else
        {
            Trie *new_trie = new Trie(s.substr(i));
            new_trie->cnt++;

            if (!next)
                next = new LinkedList(new_trie);
            else
                next->push_back(new_trie);
        }
    }

    int count(string &s, int i)
    {

        //cout << "i: " << i << " key: " << this->key << " cnt: " << this->cnt << "\n";
        if (i == s.size())
            return cnt;

        int cur = s[i] - 'a';
        Trie *ptr = next_trie(s[i]);

        if (ptr)
        {
            int j = 0;
            for (; j < ptr->key.size() && i + j < s.size(); j++)
                if (s[i + j] != ptr->key[j])
                    break;
            return (j == ptr->key.size() ? cnt + ptr->count(s, i + j) : cnt);
        }
        else
            return cnt;
    }

    void find(string &s, int i, vector<string> &ret)
    {
        if (cnt)
            return;

        Trie *ptr = next_trie(s[i]);
        ret.push_back(ptr->key);

        if (ptr)
            ptr->find(s, i + ptr->key.size(), ret);
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        Trie trie("-1");
        int n, m;
        cin >> n;
        while (n--)
        {
            string s;
            cin >> s;
            trie.insert(s, 0);
        }

        cin >> m;
        while (m--)
        {
            int ans = 0, save;
            string s;
            cin >> s;

            for (int i = 0; i < s.size(); i++)
            {
                //cout << "main: " << s.substr(i) << "\n";
                int cnt = trie.count(s, i);
                ans += cnt;
                if (cnt)
                    save = i;
            }

            //cout << "ans: " << ans << "\n";
            if (ans == 0)
                cout << "NO\n";
            else if (ans == 1)
            {
                vector<string> ret;
                trie.find(s, save, ret);
                for (auto i : ret)
                    cout << i;
                cout << "\n";
            }
            else
                cout << "AMBIGUOUS\n";
        }
    }
}