#include <stdio.h>
#include <cstring>
#define MaxL 1001
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, f, w;
	Edge *next, *opp;
}
adj[MaxL], memo[50000];

int vis[MaxL];
int c[3], C, c1, c2;
int m, n, mset, s, t, Min;
int Q[MaxL], head, tail, in[MaxL], cnt[MaxL];
int dist[MaxL], flag;
int P1[MaxL], t1, P2[MaxL], t2;
int g[MaxL][MaxL];
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
	mset = 0;
	for(int i=0; i<n; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, 1, c);
		addEdge(b, a, 1, c);
	}
	s = 1, t = n;
	memset(g, 0, sizeof g);
}

bool spfa(int s, int t)
{
	for(int i=0; i<=n; ++i) dist[i] = INF;
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
				if(!in[v])// && cnt[v]<=n)
				{
					Q[tail] = v;
					tail = (tail + 1) % MaxL;
					in[v] = 1;
					//cnt[v]++;
				}
			}
		}
	}
	if(dist[t] < INF) c[C+1] = dist[t];
	return dist[t] < INF;
}

void dfs(int now, int a[], int& top, int& c)
{
	if(flag) return;
	a[++top] = now;
	if(now==t)
	{
		flag = 1;
		return;
	}
	vis[now] = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(ptr->opp->f && !vis[k])
		{
			if(ptr->w < 0) continue;
			if(g[now][k] || g[k][now]) continue;
			g[now][k] = g[k][now] = 1;
			c += ptr->w;
			//printf("%d %d %d %d\n", now, ptr->idx, ptr->opp->f, ptr->w);
			dfs(k, a, top, c);
		}
		if(flag) return;
	}
}

void out(int a[], int top)
{
	for(int i=1; i<=top; ++i)
	{
		printf("%d", a[i]);
		if(i==top) puts("");
		else printf(" ");
	}
}

void cost_flow(int s, int t)
{
	c[0] = c[1] = c[2] = -1;
	C = 0;
	while(spfa(s, t))
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
		C++;
		if(C==2) break;
	}
	if(C < 2) printf("No solution\n");
	else
	{
		t1 = t2 = 0;
		c1 = c2 = 0;
		memset(vis, 0, sizeof vis);
		flag = 0;
		dfs(s, P1, t1, c1);
		memset(vis, 0, sizeof vis);
		flag = 0;
		dfs(s, P2, t2, c2);

		//printf("%d %d\n", c1, c2);

		printf("%d\n", c1+c2);

		/*
		if(c1 != c2) puts("No solution");
		else
		{
			out(P1, t1);
			out(P2, t2);
		}
		*/
	}
}

void solve()
{
	cost_flow(s, t);
}

int main()
{
	while(scanf("%d%d", &n, &m)!=EOF)
	{

		init();
		solve();
	}
	return 0;
}

