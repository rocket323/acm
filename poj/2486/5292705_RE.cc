#include <stdio.h>
#include <cstring>
#define MaxL 229
#define INF 0x3f3f3f3f
#define Max(a,b) ((a>b)?a:b)

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[2*MaxL];

int n, K, mset, w[MaxL], p[MaxL];
int f[MaxL][MaxL][2];
int g[MaxL][2][MaxL];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d", &w[i]);
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
		if(p[now] != ptr->idx)
		{
			p[ptr->idx] = now;
			dfs(ptr->idx);
		}
	}
}

int dp(int now, int s, int t)
{

	if(f[now][s][t] != -1) return f[now][s][t];
	
	//printf("%d %d %d\n", now, s, t);

	memset(g[now], 0x80, sizeof g[now]);
	g[now][0][0] = 0;
	if(t==1)
	{
		int idx = 0;
		
		for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
		{
			int k = ptr->idx;
			idx ^= 1;
			if(p[k] != now){ idx ^= 1; continue; }
			for(int j=0; j<=s; ++j)
			{
				g[now][idx][j] = g[now][idx^1][j];
				for(int x=2; x<=j; ++x)
				{
					if(g[now][idx^1][j-x]<=-INF || dp(k, x-2, 1)<=-INF) continue;
					g[now][idx][j] = Max(g[now][idx][j], g[now][idx^1][j-x] + dp(k, x-2, 1));
				}
			}
		}
		return f[now][s][1] = g[now][idx][s] + w[now];
	}
	else
	{
		f[now][s][t] = 0;
		for(Edge *pp=adj[now].next; pp; pp=pp->next)
		{
			if(p[pp->idx]!=now) continue;
			memset(g[now], 0x80, sizeof g[now]);
			g[now][0][0] = 0;
			int idx = 0;
			for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
			{
				int k = ptr->idx;
				idx ^= 1;
				if(p[k] != now){ idx ^= 1; continue; }
				
				for(int j=0; j<=s; ++j)
				{
					g[now][idx][j] = g[now][idx^1][j];
					if(pp == ptr)
					{
						for(int x=1; x<=j; ++x)
						{
							if(g[now][idx^1][j-x]<=-INF || dp(k, x-1, 0)<=-INF) continue;
							g[now][idx][j] = Max(g[now][idx][j], g[now][idx^1][j-x] + dp(k, x-1, 0));
						}
					}
					else
					{
						for(int x=2; x<=j; ++x)
						{
							if(g[now][idx^1][j-x]<=-INF || dp(k, x-2, 1)<=-INF) continue;
							g[now][idx][j] = Max(g[now][idx][j], g[now][idx^1][j-x] + dp(k, x-2, 1));
						}
					}
				}
			}
			f[now][s][0] = Max(f[now][s][0], g[now][idx][s]);
		}
		return f[now][s][0] = f[now][s][0] + w[now];
	}
}

void solve()
{
	memset(f, -1, sizeof f);
	memset(p, -1, sizeof p);
	dfs(1);
	int ans = -INF;
	for(int i=0; i<=K; ++i)
	{
		int x = dp(1, i, 0);
		if(x > ans) ans = x;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &K)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
