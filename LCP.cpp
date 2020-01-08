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

void radix_sort(vector<pair<pii, int>> &vec, int num)
{
    int size = vec.size();
    vector<pair<pii, int>> temp;
    temp.resize(size);

    vector<int> cnt;
    cnt.resize(num + 1);
    for (int i = 0; i < size; i++)
        cnt[vec[i].first.second + 1]++;
    for (int i = 1; i < num + 1; i++)
        cnt[i] += cnt[i - 1];
    for (int i = size - 1; i >= 0; i--)
        temp[--cnt[vec[i].first.second + 1]] = vec[i];

    cnt.resize(num);
    fill(cnt.begin(), cnt.end(), 0);

    for (int i = 0; i < size; i++)
        cnt[temp[i].first.first]++;
    for (int i = 1; i < num; i++)
        cnt[i] += cnt[i - 1];
    for (int i = size - 1; i >= 0; i--)
        vec[--cnt[temp[i].first.first]] = temp[i];
}

vector<int> get_suffix_array(string s)
{
    int len = s.length();

    vector<pair<pii, int>> sa_node;
    vector<int> pos;
    pos.resize(len);

    for (int i = 0; i < len; i++)
    {
        pii rank(s[i] - 'a', i == len - 1 ? -1 : s[i + 1] - 'a');
        sa_node.push_back(make_pair(rank, i));
    }

    sort(sa_node.begin(), sa_node.end());

    for (int d = 2; d < len; d <<= 1)
    {
        int num_rank = 0, tmp = sa_node[0].first.first;
        sa_node[0].first.first = 0;
        pos[sa_node[0].second] = 0;

        for (int i = 1; i < len; i++)
        {
            pii pair_tmp(tmp, sa_node[i - 1].first.second);
            if (pair_tmp == sa_node[i].first)
                sa_node[i].first.first = num_rank;
            else
            {
                tmp = sa_node[i].first.first;
                sa_node[i].first.first = ++num_rank;
            }
            pos[sa_node[i].second] = i;
        }
        ++num_rank;

        for (int i = 0; i < len; i++)
        {
            int j = sa_node[i].second + d;
            if (j < len)
                sa_node[i].first.second = sa_node[pos[j]].first.first;
            else
                sa_node[i].first.second = -1;
        }

        radix_sort(sa_node, num_rank);
    }

    vector<int> sa;
    for (int i = 0; i < len; i++)
        sa.push_back(sa_node[i].second);
    return sa;
}

vector<int> get_lcp(string s, vector<int> sa)
{
    int len = sa.size();
    vector<int> rnk(len), lcp(len - 1);

    for (int i = 0; i < len; i++)
        rnk[sa[i]] = i;

    for (int i = 0, k = 0; i < len; i++)
    {
        if (rnk[i] == len - 1)
            continue;
        for (int j = sa[rnk[i] + 1]; i + k < len && j + k < len && s[i + k] == s[j + k]; k++)
            ;
        lcp[rnk[i]] = k;
        if (k > 0)
            k--;
    }

    return lcp;
}

// sa[2] = 3 이라 치면 [3, N) 의 부분문자열을 정렬했을 때, 2번째라는 뜻
// sa[i] = j 일 때, [j, N) 의 부분문자열이 정렬했을 때 i번째 위치에 있음을 뜻함
// lcp[0] 는 정렬했을때 0번째와 1번째 문자열이 몇칸 겹치는 지 저장
// lcp[i] 는 정렬했을 때 i번째와 i+1번째 문자열이 몇 칸 겹치는지 저장
// lcp[i] 는 [sa[i], N) 과 [sa[i+1], N) 이 몇 칸 겹치는지 저장

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    string s, t;
    cin >> s >> t;
    string st = s + "$" + t;

    int n = s.size(), m = t.size();

    vector<int> sa = get_suffix_array(st);
    vector<int> lcp = get_lcp(st, sa);

    int ans = 0;
    for (int i = 0; i < lcp.size(); i++)
    {
        int j = sa[i];
        int k = sa[i + 1];
        int l = lcp[i];

        if (j < n && n < k)
        {
            //cout << st.substr(j, l) << " " << st.substr(k, l) << "\n";
            //cout << j << " " << k << " " << l << "\n";
            ans = max(ans, l);
        }

        if (k < n && n < j)
        {
            //cout << st.substr(j, l) << " " << st.substr(k, l) << "\n";
            //cout << j << " " << k << " " << l << "\n";
            ans = max(ans, l);
        }
    }
    cout << ans;
}