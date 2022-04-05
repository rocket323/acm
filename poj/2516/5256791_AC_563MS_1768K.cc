#include <stdio.h>
#define INF 0x3f3f3f3f
#define MaxL 123

struct Edge
{
	int idx, f, w;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL*MaxL*10];

int n, m, k, mset;
int A[MaxL][MaxL], B[MaxL][MaxL], d[MaxL][MaxL][MaxL];
int dist[MaxL], t, s;
Edge *pre[MaxL];

void addEdgeProcess(int a, int b, int c, int w)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->f = c; ptr->w = w;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c, int w)
{
	addEdgeProcess(a, b, c, w);
	addEdgeProcess(b, a, 0, -w);
	adj[a].next->opp = &memo[mset-1];
	adj[b].next->opp = &memo[mset-2];
}

void init()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=k; ++j) scanf("%d", &A[i][j]);
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=k; ++j) scanf("%d", &B[i][j]);
	for(int i=1; i<=k; ++i)
	{
		for(int r=1; r<=n; ++r)
		{
			for(int c=1; c<=m; ++c)
			{
				scanf("%d", &d[i][r][c]);
				//if(i==1) printf("%d ", d[i][r][c]);
			}
			//if(i==1)printf("\n");
		}
	}
}

void make_Gra(int k)
{
	mset = 0;
	s = 0; t = n + m + 1;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	
	for(int i=1; i<=n; ++i) addEdge(s, i, A[i][k], 0);
	for(int i=1; i<=m; ++i) addEdge(i+n, t, B[i][k], 0);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			addEdge(i, j+n, INF, d[k][i][j]);
		}
	}
}

bool bellman_ford()
{
	for(int i=s; i<=t; ++i) dist[i] = INF;
	dist[s] = 0;
	bool flag = 1;
	
	for(int x=s; x<t && flag; ++x)
	{
		flag = 0;
		for(int i=s; i<=t; ++i)
		{
			for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
			{
				if(ptr->f<=0) continue;
				int k = ptr->idx;
				if(dist[i] + ptr->w < dist[k])
				{
					dist[k] = dist[i] + ptr->w;
					pre[k] = ptr;
					flag = 1;
				}
			}
		}
	}
	return dist[t] < INF;
}

bool check()
{
	for(Edge *ptr=adj[s].next; ptr; ptr=ptr->next)
	{
		if(ptr->f > 0) return 0;
	}
	return 1;
}

int min_flow()
{
	int ans = 0;
	while(bellman_ford())
	{
		int k = t, Min = INF + 10;
		while(k != s)
		{
			if(pre[k]->f < Min) Min = pre[k]->f;
			k = pre[k]->opp->idx;
		}
		k = t;
		while(k != s)
		{
			pre[k]->f -= Min;
			pre[k]->opp->f += Min;
			k = pre[k]->opp->idx;
		}
		//printf("h %d %d\n",Min, dist[t]);
		ans += Min * dist[t];
	}
	return ans;
}

void solve()
{
	int ans = 0;
	for(int i=1; i<=k; ++i)
	{
		make_Gra(i);
		int p = min_flow();
		if(!check())
		{
			printf("-1\n");
			return;
		}
		ans += p;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d%d", &n, &m, &k) && (n+m+k))
	{
		init();
		solve();
	}
	return 0;
}
