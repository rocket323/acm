#include <stdio.h>
#include <cstring>
#define maxl 3010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, cst;
	Edge *next;
}
adj[maxl], memo[maxl * 4];

int n, m, w[maxl], mset, p[maxl], f[maxl][maxl];
int sz[maxl];

int max(int a, int b){ return (a>b)?a:b; }
int min(int a, int b){ return (a<b)?a:b; }

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->cst = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d%d", &n, &m);
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;

	for(int i=1; i<=n-m; ++i)
	{
		int k, a, b;
		scanf("%d", &k);
		for(int j=0; j<k; ++j)
		{
			scanf("%d%d", &a, &b);
			addEdge(i, a, b);
		}
	}
	memset(w, 0, sizeof w);
	for(int i=n-m+1; i<=n; ++i) scanf("%d", &w[i]);
}

void dp(int now)
{
	for(int i=0; i<=m; ++i) f[now][i] = -INF;

	f[now][0] = 0;
	if(now > n - m) f[now][1] = w[now];
	
	sz[now] = (now > n - m);

	int sum = sz[now];
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] == k) continue;

		p[k] = now;

		dp(k);

		sum += sz[k];
		for(int i=min(m, sum); i>=0; --i)
		{
			for(int j=max(1, i-sum+sz[k]); j<=min(i, sz[k]); ++j) f[now][i] = max(f[now][i], f[now][i-j] + f[k][j] - ptr->cst);
		}
	}

	sz[now] = sum;
}

void solve()
{
	memset(p, -1, sizeof p);
	dp(1);

	for(int i=m; i>=0; --i)
	{
		if(f[1][i] >= 0)
		{
			printf("%d\n", i);
			return;
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}

