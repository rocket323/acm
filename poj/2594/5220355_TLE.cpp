#include <stdio.h>
#include <cstring>
#define MaxL 520

struct Edge
{
	int idx;
	Edge * next;
}
adj[MaxL], memo[100*MaxL];

int g[MaxL][MaxL], vis[MaxL], mset, lik[MaxL];
int n, m;
int Q[MaxL], head, tail;

void addEdge(int a, int b)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	memset(g, 0, sizeof g);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = 1;
		addEdge(a, b);
	}
}

void bfs(int s)
{
	head = 0, tail = 1;
	Q[0] = s;
	memset(vis, 0, sizeof vis);
	vis[s] = 1;
	while(head < tail)
	{
		int k = Q[head];
		Edge * ptr = adj[k].next;
		while(ptr)
		{
			if(!g[s][ptr->idx]) g[s][ptr->idx] = 1;
			if(!vis[ptr->idx])
			{
				vis[ptr->idx] = 1;
				Q[tail++] = ptr->idx;
			}
			ptr = ptr->next;
		}
		++head;
	}
}

void make_Gra()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			if(g[i][j]) addEdge(i, j);
		}
	}
}

bool can(int now)
{
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(!vis[k])
		{
			vis[k] = 1;
			if(lik[k]==-1 || can(lik[k]))
			{
				lik[k] = now;
				return 1;
			}
		}
	}
	return 0;
}

void solve()
{
	for(int i=1; i<=n; ++i) bfs(i);
	make_Gra();
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=n; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	printf("%d\n", n-ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n+m))
	{
		init();
		solve();
	}
	return 0;
}
