#include <stdio.h>
#include <cstring>
#define MaxL 1001
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[MaxL], memo[2*MaxL];

int f[MaxL][MaxL], d[MaxL][MaxL], p[MaxL], mset;
int sub[MaxL][MaxL], w[MaxL], D[MaxL], n;
int g[MaxL][MaxL], cnt[MaxL];

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &w[i]);
	for(int i=1; i<=n; ++i) scanf("%d", &D[i]);
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<n; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void dfs(int root, int now, int len)
{
	d[root][now] = len;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] != k)
		{
			p[k] = now;
			dfs(root, k, len+ptr->len);
		}
	}
}

void dfs2(int root, int now)
{
	if(!sub[root][now])
	{
		sub[root][now] = 1;
		g[root][++cnt[root]] = now;
	}
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		if(p[ptr->idx] == now) dfs2(root, ptr->idx);
	}
}

int dp(int i, int j)
{
	if(f[i][j] != -1) return f[i][j];
	
	if(d[i][j] > D[i]) return INF;
	
	int ans = 0;
	for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[k] != i) continue;
		
		if(sub[k][j])
		{
			if(ans < INF) ans += dp(k, j);
			else break;
		}
		else
		{
			int Min = dp(k, j);
			for(int x=1; x<=cnt[k]; ++x)
			{
				int a = g[k][x];
				if(d[a][i] < d[i][j]) continue;
				Min = min(Min, dp(k, a) + w[a]);
			}
			
			if(ans < INF) ans += Min;
			else break;
		}
	}
	return f[i][j] = ans;
}

void solve()
{
	memset(f, -1, sizeof f);
	for(int i=1; i<=n; ++i)
	{
		memset(p, -1, sizeof p);
		dfs(i, i, 0);
	}
	memset(p, -1, sizeof p);
	dfs(1, 1, 0);
	memset(sub, 0, sizeof sub);
	memset(cnt, 0, sizeof cnt);
	for(int i=1; i<=n; ++i) dfs2(i, i);
	int ans = INF;
	for(int i=1; i<=n; ++i)
	{
		if(d[1][i] > D[1]) continue;
		int k = dp(1, i) + w[i];
		if(k != -1 && k < ans) ans = k;
	}
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
