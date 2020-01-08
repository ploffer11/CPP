#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ui = unsigned int;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MOD = (ll)1 << 32;
const int MAX = 100005;

struct Info
{
    ui dp_value, sum, h;
};

vector<int> adj[MAX];
Info info[MAX];

ll save[MAX];
ui dp[MAX], M[MAX], udp[MAX], power[MAX];
int visit[MAX], parent[MAX], S[MAX], E[MAX];

void dfs(int s)
{
    visit[s] = true;
    bool leaf = true;
    vector<Info> temp;

    ui h_max = 0, sum_sum = 0, dp_sum = 0;
    for (auto e : adj[s])
    {
        if (!visit[e])
        {
            leaf = false;
            dfs(e);
            auto [x, y, z] = info[e];
            dp_sum += x;
            sum_sum += y;
            h_max = max(z, h_max);
            temp.push_back(info[e]);
            parent[e] = s;
        }
    }

    if (leaf)
    {
        info[s] = {power[s], power[s], 1};
        return;
    }

    dp_sum += (h_max + 1) * power[s];
    for (auto [_, sum, h] : temp)
        dp_sum += (h_max - h) * sum;

    info[s] = {dp_sum, (sum_sum + power[s]), (h_max + 1)};

    return;
}

void dfs2(int s, ui dp_sum, ui s_sum, ui h_sum, ui hs_sum, int h_max)
{
    priority_queue<int, vector<int>, less<int>> pq;
    pq.push(h_max + 1);

    ui new_dp_sum = (dp_sum + (h_max + 1) * power[parent[s]]) + (h_max * s_sum) - hs_sum;

    if (s == 1)
        new_dp_sum = 0;

    dp[s] = new_dp_sum;

    ui new_s_sum = s_sum + power[parent[s]];
    ui new_h_sum = h_max + 1;
    ui new_hs_sum = (h_max + 1) * new_s_sum;

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            new_dp_sum += info[e].dp_value;
            new_s_sum += info[e].sum;
            new_h_sum += info[e].h;
            new_hs_sum += info[e].sum * info[e].h;

            pq.push(info[e].h);
        }
    }

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            int h = -1;
            if (pq.top() == info[e].h)
            {
                pq.pop();
                h = pq.top();
                pq.push(info[e].h);
            }
            else
                h = pq.top();

            dfs2(e, new_dp_sum - info[e].dp_value, new_s_sum - info[e].sum, new_h_sum - info[e].h, new_hs_sum - info[e].h * info[e].sum, h);
        }
    }
}

void dfs4(int s, ui k)
{
    k = max(k, dp[s]);

    udp[s] = k;

    ui m_big = 0, m_small = 0;

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            if (m_big <= M[e])
            {
                m_small = m_big;
                m_big = M[e];
            }
            else if (m_small <= M[e])
                m_small = M[e];
        }
    }

    for (auto e : adj[s])
    {
        if (parent[e] == s)
        {
            if (m_big == M[e])
                dfs4(e, max(k, m_small));
            else
                dfs4(e, max(k, m_big));
        }
    }
}

ui dfs3(int s)
{
    ui ret = info[s].dp_value;
    for (auto e : adj[s])
        if (parent[e] == s)
            ret = max(ret, dfs3(e));
    return M[s] = ret;
}

char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}

int readInt()
{
    int t, r = read() & 15;
    while ((t = read()) & 16)
        r = r * 10 + (t & 15);
    return r;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    n = readInt();
    m = readInt();
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        u = readInt(), v = readInt();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        power[i] = readInt();

    dfs(1);
    dfs2(1, 0, 0, 0, 0, -1);
    dfs3(1);
    dfs4(1, 0);

    memset(save, 0x3f, sizeof(save));

    while (m--)
    {
        int s = readInt();

        if (save[s] != INF)
        {
            cout << save[s] << "\n";
            continue;
        }

        ll ans = -INF;

        for (auto e : adj[s])
        {
            if (parent[e] == s)
            {
                ui my_score = M[e];
                ui enemy_score = dp[e];

                ans = max(ans, (ll)my_score - enemy_score);
            }
            else
            {
                ui my_score = udp[s];
                ui enemy_score = info[s].dp_value;

                ans = max(ans, (ll)my_score - enemy_score);
            }
        }

        cout << ans << "\n";
        save[s] = ans;
    }
}