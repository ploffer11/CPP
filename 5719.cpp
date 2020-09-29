#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string.h>
using namespace std;
typedef pair<int, int> pii;
const int MAX = 501;

priority_queue<pii, vector<pii>, greater<pii>> pq;

vector<int> via[MAX];
vector<pii> adj2[MAX];
int adj[MAX][MAX];

int dis[MAX];
int found[MAX];

int N, M, S, D, A, B, C;
const int Big = 987654321;

int dijkstra(int start, int end);
void removeit(int end);

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
	while ( 1 )
	{
		memset(adj, 0, sizeof(adj));
		cin >> N >> M;
		if ( N + M == 0 ) break;
		cin >> S >> D;
		while ( M-- )
		{
			cin >> A >> B >> C;
			adj[A][B] = C;
		}

		dijkstra(S, D);
		removeit(D);
		int Ans = dijkstra(S, D);
		if ( Ans == Big ) cout << "-1\n";
		else cout << Ans << "\n";
	}
}

int dijkstra(int start, int end)
{
	for ( int i = 0; i < N; i++ )
	{
		dis[i] = Big;
		found[i] = 0;
		via[i].clear();
	}
	dis[start] = 0;
	pq.push(pii(0, start));
	for ( int i = 0; i < N; i++ )
	{
		int x = -1;
		while ( !pq.empty() )
		{
			cout << i << " <- " << endl;
			x = pq.top().second;
			pq.pop();
			if (found[x])
				continue;
			found[x] = 1;
			for (auto [j, w] : adj2[x])
			{
				if ( adj[x][j] == 0 ) 
					continue;
				int Node = j, Weight = adj[x][j];
				if ( dis[x] + Weight < dis[Node] )
				{
					dis[Node] = dis[x] + Weight;
					if ( via[Node].empty() ) 
						via[Node].push_back(x);
					else
					{
						via[Node].clear();
						via[Node].push_back(x);
					}
					pq.push(pii(dis[Node], Node));
				}
				else if ( dis[x] + Weight == dis[Node] )
				{
					via[Node].push_back(x);
				}
			}
		}
	}
	return dis[end];
}

void removeit(int end)
{
	for ( auto j : via[end] )
	{
		adj[j][end] = 0;
		removeit(j);
	}
}