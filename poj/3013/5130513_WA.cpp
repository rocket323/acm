#include <stdio.h>
#include <algorithm>
#include <queue>
#define INF 100000000
#define ll long long
#define MaxL 50010
using namespace std;

struct Edge
{
	int idx, w;
	Edge *next;
}
adj[MaxL], memo[2*MaxL];

struct Heap
{
	int id, w;
	Heap(int x, int y):id(x), w(y){}
};

struct cmp
{
	bool operator()(Heap A, Heap B){ return A.w > B.w; }
};

int n, m, mset;
int v[MaxL], d[MaxL];
priority_queue<Heap, vector<Heap>, cmp> pq;

void addEdge(int a, int b, int c)
{
	Edge* ptr = &memo[mset++];
	ptr->idx = b; ptr->w = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	while(!pq.empty()) pq.pop();
	scanf("%d%d", &n, &m);
	for(int i=0; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i) scanf("%d", &v[i]);
	for(int i=1; i<=m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void dijkstra(int s)
{
	for(int i=0; i<=n; ++i) d[i] = INF;
	d[s] = 0;
	pq.push(Heap(s, 0));
	while(!pq.empty())
	{
		Heap now = pq.top();
		pq.pop();
		if(now.w > d[now.id]) continue;
		Edge * ptr = adj[now.id].next;
		while(ptr)
		{
			int k = ptr->idx;
			if(d[now.id] + ptr->w < d[k])
			{
				d[k] = d[now.id] + ptr->w;
				pq.push(Heap(k, d[now.id] + ptr->w));
			}
			ptr = ptr->next;
		}
	}

}

void solve()
{
	dijkstra(1);
	int ans = 0;
	for(int i=1; i<=n; ++i) ans += (ll)d[i] * v[i];
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
