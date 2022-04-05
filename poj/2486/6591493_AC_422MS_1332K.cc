#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 220

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxl * 2];

int mset, w[maxl];
int f[maxl][maxl][2], g[maxl][maxl][2], n, k, p[maxl], ans;

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
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=1; i<=n; ++i) scanf("%d", &w[i]);
	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void dp(int now)
{
	int idx = 0;

	memset(g, 0, sizeof g);

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		if(p[now] == v) continue;
		p[v] = now;
		dp(v);
	}

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		idx++;

		for(int j=0; j<=k; ++j)
		{

			g[idx][j][0] = g[idx-1][j][0];
			g[idx][j][1] = g[idx-1][j][1];

			for(int x=0; x<=j-2; ++x)
			{
				g[idx][j][0] = max(g[idx][j][0], g[idx-1][x][0] + f[v][j-2-x][0]);
				g[idx][j][1] = max(g[idx][j][1], g[idx-1][x][1] + f[v][j-2-x][0]);
				//printf("n %d %d %d %d %d %d\n", now, v, idx, j, g[idx][j][0], g[idx][j][1]);
			}
			for(int x=0; x<=j-1; ++x)
			{
				g[idx][j][1] = max(g[idx][j][1], g[idx-1][x][0] + f[v][j-1-x][1]);
				//printf("n %d %d %d %d %d %d\n", now, v, idx, j, g[idx][j][0], g[idx][j][1]);
			}
		}
	}

	for(int i=0; i<=k; ++i)
	{
		f[now][i][0] = g[idx][i][0] + w[now];
		f[now][i][1] = g[idx][i][1] + w[now];
	}

	/*
	printf("%d : \n", now);
	for(int i=0; i<=k; ++i)
	{
		printf("%d %d\n", f[now][i][0], f[now][i][1]);
	}
	*/
}

void solve()
{
	memset(p, -1, sizeof p);
	memset(f, 0, sizeof f);

	dp(1);

	ans = 0;
	for(int i=0; i<=k; ++i) ans = max(ans, max(f[1][i][0], f[1][i][1]));
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &k) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

