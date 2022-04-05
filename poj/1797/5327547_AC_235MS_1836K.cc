#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x7f7f7f7f
#define MaxL 1001
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[MaxL], memo[100*MaxL];

struct node
{
	int id, w;
	node(int a, int b) : id(a), w(b){}
};

struct cmp
{
	bool operator()(node A, node B){ return A.w < B.w; }
};

int d[MaxL], n, m, mset, vis[MaxL];
priority_queue<node, vector<node>, cmp> pq;

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d%d", &n, &m);
	
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	
	for(int i=0; i<m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void solve(int cs)
{

	printf("Scenario #%d:\n", cs);

	memset(d, 0, sizeof d);
	d[1] = INF;
	
	while(!pq.empty()) pq.pop();
	pq.push(node(1, INF));
	
	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();
		if(now.w < d[now.id]) continue;
		if(now.id==n) break;
		for(Edge *ptr=adj[now.id].next; ptr; ptr=ptr->next)
		{
			int tmp = min(now.w, ptr->len);
			if(tmp > d[ptr->idx])
			{
				d[ptr->idx] = tmp;
				pq.push(node(ptr->idx, d[ptr->idx]));
			}
		}
	}
	
	printf("%d\n\n", d[n]);
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int i=1; i<=t; ++i)
	{
		init();
		solve(i);
	}
	return 0;
}