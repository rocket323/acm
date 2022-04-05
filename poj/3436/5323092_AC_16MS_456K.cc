#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define MaxL 200
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, f, flag;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL * MaxL * 4];

struct node
{
	int a, b, c;
}
E[MaxL * MaxL];

int in[MaxL][10], out[MaxL][10], p, n, C[MaxL], sz;
int Q[MaxL], head, tail, P[MaxL], top, lv[MaxL], mset, s, t;
Edge *pre[MaxL], *cur[MaxL];

bool isProducer(int a[])
{
	for(int i=0; i<p; ++i) if(a[i]==1) return 0;
	return 1;
}

void addEdgeProcess(int a, int b, int c, int flag)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->f = c;
	ptr->flag = flag;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c)
{
	addEdgeProcess(a, b, c, 1);
	addEdgeProcess(b, a, 0, 0);
	adj[a].next->opp = &memo[mset-1];
	adj[b].next->opp = &memo[mset-2];
}

bool isConsumer(int a[])
{
	for(int i=0; i<p; ++i) if(a[i]==0) return 0;
	return 1;
}

bool check(int a, int b)
{
	for(int i=0; i<p; ++i)
	{
		if(in[b][i]==1 && out[a][i]==0) return 0;
		if(in[b][i]==0 && out[a][i]==1) return 0;
	}
	return 1;
}

void init()
{
	mset = 0;
	s = 0, t = 2 * n + 1;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &C[i]);
		for(int j=0; j<p; ++j) scanf("%d", &in[i][j]);
		for(int j=0; j<p; ++j) scanf("%d", &out[i][j]);
		if(isProducer(in[i])) addEdge(s, i, INF);
		if(isConsumer(out[i])) addEdge(i+n, t, INF);
		addEdge(i, i+n, C[i]);
	}
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			if(i==j) continue;
			if(check(i, j)) addEdge(i+n, j, INF);
		}
	}
}

bool bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	lv[s] = 0;
	Q[head = 0] = s; tail = 1;
	
	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(lv[ptr->idx]==-1 && ptr->f>0)
			{
				Q[tail++] = ptr->idx;
				lv[ptr->idx] = lv[k] + 1;
			}
		}
		++head;
	}
	return lv[t] != -1;
}

int Dinic(int s, int t)
{
	int u, v, flow = 0;
	while(bfs(s, t))
	{
		for(int i=s; i<=t; ++i) cur[i] = adj[i].next;
		P[top = 1] = u = s;
		while(cur[s])
		{
			if(u!=t && cur[u] && cur[u]->f>0 && lv[cur[u]->idx]==lv[u]+1)
			{
				v = cur[u]->idx;
				P[++top] = v;
				pre[v] = cur[u];
				u = v;
			}
			else if(u==t)
			{
				int Min = INF;
				for(int i=top; i>1; --i) Min = min(Min, pre[P[i]]->f);
				for(int i=top; i>1; --i)
				{
					pre[P[i]]->f -= Min;
					pre[P[i]]->opp->f += Min;
					if(pre[P[i]]->f==0) top = i - 1;
				}
				flow += Min;
				u = P[top];
			}
			else
			{
				while(u!=s && cur[u]==NULL) u = P[--top];
				cur[u] = cur[u]->next;
			}
		}
	}
	return flow;
}

void cnt_flow()
{
	sz = 0;
	for(int i=n+1; i<=2*n; ++i)
	{
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			if(ptr->flag==0 || ptr->opp->f==0) continue;
			if(ptr->idx<1 || ptr->idx>n) continue;
			sz++;
			E[sz].a = i - n;
			E[sz].b = ptr->idx;
			E[sz].c = ptr->opp->f;
		}
	}
	printf(" %d\n", sz);
	for(int i=1; i<=sz; ++i) printf("%d %d %d\n", E[i].a, E[i].b, E[i].c);
}

void solve()
{
	printf("%d", Dinic(s, t));
	cnt_flow();
}

int main()
{
	while(scanf("%d%d", &p, &n)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
