#include <stdio.h>
#include <cstring>

struct Edge
{
	int idx;
	Edge * next;
}
adj[121], memo[50000];

int g[300][300], n, m, mset;
int vis[300];
int lik[300];

void addEdge(int a, int b)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d%d", &n, &m);
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b+n);
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
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=n; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	ans = n - ans;
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
