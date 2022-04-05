#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define MaxL 1010
#define max(a,b) ((a>b)?a:b)

int n, x[MaxL], y[MaxL], c[MaxL], mset, p[MaxL], f[MaxL][2];

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[MaxL * 2];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	for(int i=0; i<n; ++i) scanf("%d%d%d", &x[i], &y[i], &c[i]);
	mset = 0;
	for(int i=0; i<n; ++i) adj[i].next = NULL;

	for(int i=0; i<n; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			if(abs(x[i]-x[j]) + abs(y[i]-y[j]) == 1)
			{
				addEdge(i, j);
				addEdge(j, i);
			}
		}
	}
}

void dp(int now)
{
	f[now][0] = 0;
	f[now][1] = c[now];

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] != k)
		{
			p[k] = now;
			dp(k);

			f[now][0] = max(f[now][0], max(f[k][0], f[k][1]));
			f[now][1] = max(f[now][1], f[now][1] + f[k][1]);
		}
	}


}

void solve()
{
	/*
	for(int i=0; i<n; ++i)
	{
		printf("%d : ", i);
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			printf("%d ", ptr->idx);
		}
		puts("");
	}
	*/

	memset(f, -1, sizeof f);
	memset(p, -1, sizeof p);
	dp(0);
	printf("%d\n", max(f[0][0], f[0][1]));
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

