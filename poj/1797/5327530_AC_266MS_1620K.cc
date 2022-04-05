#include <stdio.h>
#include <cstring>
#define INF 0x7f7f7f7f
#define MaxL 1001
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[MaxL], memo[100*MaxL];

int d[MaxL], n, m, mset, vis[MaxL];

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

	memset(vis, 0, sizeof vis);
	memset(d, 0, sizeof d);
	d[1] = INF;
	
	for(int x=1; x<=n; ++x)
	{
		int k = -1, Max = -INF;
		for(int i=1; i<=n; ++i)
		{
			if(!vis[i] && d[i]>Max)
			{
				Max = d[i];
				k = i;
			}
		}
		if(k==n) break;
		vis[k] = 1;
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			int tmp = min(d[k], ptr->len);
			if(tmp > d[ptr->idx]) d[ptr->idx] = tmp;
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