#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <functional>
#include <string.h>
using namespace std;
typedef long long ll;
typedef tuple<ll, ll, ll> t;
typedef pair<int, int> pii;

vector<pii> vt[10005];

int n, m, k;
ll dis[10005][21];
bool found[10005][21];

ll dajik()
{
	for ( int j = 0; j <= k; j++ )
	{
		for ( int i = 1; i <= n; i++ ) dis[i][j] = 1e13;
	}
	
	priority_queue<t, vector<t>, greater<t>> pq;
	pq.push(t(0, 0, 1));
	dis[1][0] = 0;

	while ( !pq.empty() )
	{
		auto[cur, K, node] = pq.top();
		pq.pop();

		if ( found[node][K] ) continue;

		for ( auto[dest, cost] : vt[node] )
		{
			if ( dis[dest][K] > cur + cost )
			{
				dis[dest][K] = cur + cost;
				pq.push(t(dis[dest][K], K, dest));
			}

			if ( K < k && dis[dest][K + 1] > cur )
			{
				dis[dest][K + 1] = cur;
				pq.push(t(cur, K+1, dest));
			}
		}

		found[node][K] = true;
	}
	
	ll ret = 1e13;
	
	for (int i = 0; i <= k; i++)
		ret = min(ret, dis[n][i]);

	return ret;
}

void input()
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	int a, b, c;
	cin >> n >> m >> k;
	for ( int i = 0; i < m; i++ )
	{
		cin >> a >> b >> c;
		vt[a].push_back(pii(b, c));
		vt[b].push_back(pii(a, c));
	}
}

int main()
{
	input();
	cout << dajik();
}