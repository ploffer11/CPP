#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;
int ans, t, chk;

class Trie
{
private:
    Trie *next[26];

public:
    int finish;
    int cnt;
    Trie()
    {
        finish = 0;
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
            finish = 1;
        else
        {
            int cur = *key - 'A';
            if (!next[cur])
                next[cur] = new Trie();
            next[cur]->insert(key + 1);
        }
    }

    Trie *find(char key)
    {
        int cur = key - 'A';
        return next[cur];
    }
};

Trie trie;
Trie *T;

int length, total_score;
string ans_str;

char str[15];
char board[10][10];
bool visit[10][10];
int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {1, 0, -1, 1, -1, 1, 0, -1};
vector<char> vt;

string temp;
void back_tracking(int r, int c)
{
    visit[r][c] = true;
    temp += board[r][c];

    if (T->finish > 0 && T->finish != chk)
    {
        ans++;
        T->finish = chk;
        total_score += score[temp.size()];
        if (temp.size() > length)
        {
            length = temp.size();
            ans_str = temp;
        }

        else if (temp.size() == length)
            ans_str = min(ans_str, temp);
    }

    Trie *copy = T;
    for (int i = 0; i < 8; i++)
    {
        int R = r + dr[i], C = c + dc[i];
        if (1 <= R && R <= 4 && 1 <= C && C <= 4 && !visit[R][C])
        {
            T = T->find(board[R][C]);
            if (T)
                back_tracking(R, C);
            T = copy;
        }
    }

    temp.pop_back();
    visit[r][c] = false;
}

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

    chk = 1;
    cin >> t;
    while (t--)
    {
        ++chk;
        ans = 0;
        length = 0;
        ans_str = "";
        total_score = 0;

        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                cin >> board[i][j];

        for (int i = 1; i <= 4; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                T = trie.find(board[i][j]);
                if (T)
                    back_tracking(i, j);
                T = NULL;
            }
        }
        cout << total_score << " " << ans_str << " " << ans << '\n';
    }
}