#include <stdio.h>
#include <cstring>
#define MaxL 1900
#define UNVIS 0
#define VIS 1
#define OVER 2
#define max(a,b) ((a>b)?a:b)

struct Edge
{
	int idx;
	Edge * next;
}
adj[MaxL], memo[1000000], list[MaxL];

int n, m;
int id[MaxL], mark[MaxL], low[MaxL], pre[MaxL];
int P[MaxL], top, lv;
int f[MaxL];
char g[50][50];
int mr[1900], mc[1900];
int C[1900], mset;

void addEdge(Edge adj[], int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d%d", &n, &m);
	mset = 0;
	for(int i=0; i<n*m; ++i) adj[i].next = NULL;

	memset(C, 0, sizeof C);
	int k = 0;
	for(int i=0; i<n; ++i)
	{
		scanf("%s", g[i]);
		for(int j=0; j<m; ++j)
		{
			if(g[i][j]=='*')
			{
				k++;
				mr[k] = i, mc[k] = j;
			}
			if(j<m-1 && g[i][j]!='#' && g[i][j+1]!='#') addEdge(adj, i*m+j, i*m+j+1);
			if(i<n-1 && g[i][j]!='#' && g[i+1][j]!='#') addEdge(adj, i*m+j, (i+1)*m+j);

			if(g[i][j]>='0' && g[i][j]<='9') C[i*m+j] = g[i][j] - '0';
		}
	}
	for(int i=1; i<=k; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(g[a][b] == '#') continue;
		addEdge(adj, mr[i]*m+mc[i], a*m+b);
	}
}

void dfs(int now)
{
	id[now] = low[now] = lv++;
	P[++top] = now;
	mark[now] = VIS;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;

		if(mark[k]==UNVIS)
		{
			dfs(k);
			if(low[k] < low[now]) low[now] = low[k];
		}
		else if(mark[k]==VIS)
		{
			if(low[k] < low[now]) low[now] = low[k];
		}
	}

	if(low[now] == id[now])
	{
		do
		{
			pre[P[top]] = now;
			mark[P[top]] = OVER;
		}
		while(P[top--] != now);
	}
}

void rebuild()
{
	for(int i=0; i<n*m; ++i) list[i].next = NULL;
	for(int i=0; i<n*m; ++i)
	{
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			int k = ptr->idx;
			if(pre[i] != pre[k]) addEdge(list, pre[i], pre[k]);
		}
	}
}

int dp(int now)
{
	if(f[now] != -1) return f[now];

	int tmp = 0;
	for(Edge *ptr=list[now].next; ptr; ptr=ptr->next)
	{
		tmp = max(tmp, dp(ptr->idx));
	}
	return f[now] = tmp + C[now];
}

void solve()
{
	memset(mark, 0, sizeof mark);
	for(int i=0; i<n*m; ++i)
	{
		if(mark[i]==UNVIS) dfs(i);
	}
	rebuild();

	for(int i=0; i<n*m; ++i)
	{
		if(pre[i] == i) continue;
		C[pre[i]] += C[i];
	}
	
	int ans = 0;
	memset(f, -1, sizeof f);
	printf("%d\n", dp(0));
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

