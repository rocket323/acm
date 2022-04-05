#include <stdio.h>
#include <cstring>
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
int dist[MaxL], t, s, Q[MaxL], head, tail, in[MaxL], cnt[MaxL];
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
			}
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

bool spfa()
{
	for(int i=s; i<=t; ++i) dist[i] = INF;
	dist[s] = 0;
	tail = 1;
	Q[head = 0] = s;
	memset(in, 0, sizeof in);
	memset(cnt, 0, sizeof cnt);
	in[s] = 1; cnt[s] = 1;
	while(head != tail)
	{
		int u = Q[head];
		head = (head + 1) % MaxL;
		in[u] = 0;
		for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next)
		{
			if(ptr->f <= 0) continue;
			int v = ptr->idx;
			if(dist[u] + ptr->w < dist[v])
			{
				dist[v] = dist[u] + ptr->w;
				pre[v] = ptr;
				if(!in[v]) Q[tail] = v, tail = (tail + 1) % MaxL, in[v] = 1;
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
	while(spfa())
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
