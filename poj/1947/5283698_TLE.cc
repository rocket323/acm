#include <stdio.h>
#include <cstring>
#define MaxL 151
#define INF 0x7f7f7f7f

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[2*MaxL];

int n, P, mset, p[MaxL];
int f[MaxL][MaxL], g[MaxL][MaxL][MaxL], ans;

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d%d", &n, &P);

	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=1; i<n; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void dfs(int now)
{
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		if(p[now]!=ptr->idx)
		{
			p[ptr->idx] = now;
			dfs(ptr->idx);
		}
	}
}

int Min(int a, int b){ return (a<b)?a:b; }

int dp(int now, int P)
{
	if(f[now][P]!=-1)
	{
		return f[now][P];
	}

	memset(g[now], 0x3f, sizeof g[now]);
	g[now][0][0] = 0;
	int i = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next, i++)
	{
		if(p[ptr->idx]!=now){ i--; continue; }
		for(int j=0; j<P; ++j)
		{
			g[now][i][j] = g[now][i-1][j] + 1;
			for(int k=1; k<=j; ++k)
			{
				g[now][i][j] = Min(g[now][i][j], g[now][i-1][j-k] + dp(ptr->idx, k));
			}
		}
	}


	return f[now][P] = g[now][i-1][P-1];
}

void solve()
{
	ans = INF;
	memset(p, -1, sizeof p);
	memset(f, -1, sizeof f);
	dfs(1);
	

	for(int i=1; i<=n; ++i)
	{
		if(dp(i, P) < ans) ans = dp(i, P);
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
