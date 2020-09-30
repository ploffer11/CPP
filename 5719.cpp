#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string.h>
using namespace std;
typedef pair<int, int> pii;
const int MAX = 501;
const int INF = 0x3f3f3f3f;

priority_queue<pii, vector<pii>, greater<pii>> pq;

vector<int> via[MAX];
vector<pii> adj2[MAX];
int adj[MAX][MAX];

int dis[MAX];
int found[MAX];

bool visit[MAX];

int N, M, S, D, A, B, C;

int dijkstra(int start, int end);
void removeit(int end);

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	while ( 1 )
	{
		memset(adj, 0, sizeof(adj));
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < N; i++)
			adj2[i].clear(); 
			
		cin >> N >> M;
		if ( N + M == 0 ) break;
		cin >> S >> D;
		while ( M-- )
		{
			cin >> A >> B >> C;
			adj[A][B] = C;
			adj2[A].push_back({B, C});
		}

		dijkstra(S, D);
		removeit(D);
		int Ans = dijkstra(S, D);
		
		if ( Ans == INF ) cout << "-1\n";
		else cout << Ans << "\n";
	}
}

int dijkstra(int start, int end)
{
	memset(found, 0, sizeof(found));
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 0; i < N; i++)
		via[i].clear();
	
	dis[start] = 0;
	pq.push(pii(0, start));
	
	int s;
	while ( !pq.empty() )
	{
		s = pq.top().second;
		pq.pop();
		if (found[s])
			continue;
		found[s] = 1;
		for (auto [e, w] : adj2[s])
		{
			if ( adj[s][e] == 0 ) 
				continue;
			if ( dis[s] + w < dis[e] )
			{
				dis[e] = dis[s] + w;
				if ( !via[e].empty() ) 
					via[e].clear();
				
				via[e].push_back(s);
				pq.push(pii(dis[e], e));
			}
			else if ( dis[s] + w == dis[e] )
			{
				via[e].push_back(s);
			}
		}
	}
	
	return dis[end];
}

void removeit(int e)
{
	visit[e] = true;
	for ( auto s : via[e] )
	{
		if (!visit[s])
			removeit(s);
		adj[s][e] = 0;
	}
}