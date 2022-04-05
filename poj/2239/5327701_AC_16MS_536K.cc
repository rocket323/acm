#include <stdio.h>
#include <cstring>
#define MaxL 301

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[100 * MaxL];

int n, m, mset, vis[MaxL], lik[MaxL];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		int k, p, q;
		scanf("%d", &k);
		for(int j=0; j<k; ++j)
		{
			scanf("%d%d", &p, &q);
			addEdge(i, (p-1)*12+q);
		}
	}
}

bool can(int now)
{
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(vis[k]) continue;
		vis[k] = 1;
		if(lik[k]==-1 || can(lik[k]))
		{
			lik[k] = now;
			return true;
		}
	}
	return false;
}

void solve()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=n; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	printf("%d\n", ans);
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