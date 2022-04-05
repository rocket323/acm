#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define MaxL 3000

struct Edge
{
	int idx, f, w;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL*200];

int A[MaxL][MaxL], s, t, Q[MaxL], head, tail;
int n, m, in[MaxL], mset, dist[MaxL];
Edge *pre[MaxL];

void init()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) scanf("%d", &A[i][j]);
	}
}

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

bool spfa()
{
	for(int i=s; i<=t; ++i) dist[i] = INF;
	dist[s] = 0;
	tail = 1;
	Q[head = 0] = s;
	memset(in, 0, sizeof in);
	in[s] = 1;
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
				if(!in[v]) Q[tail] = v, tail = (tail+1)%MaxL, in[v] = 1;
			}
		}
	}
	return dist[t] < INF;
}

void solve()
{
	s = 0, t = n + m * n + 1;
	mset = 0;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	
	for(int i=1; i<=n; ++i) addEdge(s, i, 1, 0);
	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			for(int k=1; k<=n; ++k) addEdge(k, n+(i-1)*n+j, 1, j*A[k][i]);
			addEdge(n+(i-1)*n+j, t, 1, 0);
		}
	}
	
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
	printf("%.6f\n", ans * 1.0 / n);
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
