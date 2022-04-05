#include <stdio.h>
#include <cstring>
#include <cmath>
#define MaxL 350
#define MaxE (MaxL*MaxL*3)
#define INF 0x3f3f3f3f

int n, m, s, t, e;

struct Graph
{
	struct Edge
	{
		int idx;
		double flow;
		Edge *next, *opp;
	}
	adj[MaxL], memo[MaxE];

	int mset, Q[MaxL], head, tail, lv[MaxL], P[MaxL], top;
	Edge *pre[MaxL], *cur[MaxL];

	void clear(int s, int ){ mset = 0; for(int i=s; i<=t; ++i) adj[i].next = NULL; }

	void addEdgeProcess(int a, int b, double c)
	{
		Edge *ptr = &memo[mset++];
		ptr->idx = b; ptr->flow = c;
		ptr->next = adj[a].next;
		adj[a].next = ptr;
	}

	void addEdge(int a, int b, double c)
	{
		addEdgeProcess(a, b, c);
		addEdgeProcess(b, a, 0);
		adj[a].next->opp = &memo[mset-1];
		adj[b].next->opp = &memo[mset-2];
	}

	bool bfs(int s, int t)
	{
		memset(lv, -1, sizeof lv);
		tail = 1;
		Q[head = 0] = s; lv[s] = 0;
		while(head < tail)
		{
			int k = Q[head];
			for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
			{
				if(fabs(ptr->flow) > 1e-6 && lv[ptr->idx]==-1)
				{
					Q[tail++] = ptr->idx;
					lv[ptr->idx] = lv[k] + 1;
				}
			}
			++head;
		}
		return lv[t] != -1;
	}

	double Dinic(int s, int t)
	{
		double flow = 0;
		int u;
		while(bfs(s, t))
		{
			P[top = 1] = u = s;
			for(int i=s; i<=t; ++i) cur[i] = adj[i].next;
			while(cur[s])
			{
				if(u!=t && cur[u] && fabs(cur[u]->flow) > 1e-6 && lv[cur[u]->idx]==lv[u]+1)
				{
					int v = cur[u]->idx;
					P[++top] = v;
					pre[v] = cur[u];
					u = v;
				}
				else if(u==t)
				{
					double Min = 1e20;
					for(int i=top; i>1; --i) if(pre[P[i]]->flow < Min) Min = pre[P[i]]->flow;
					for(int i=top; i>1; --i)
					{
						pre[P[i]]->flow -= Min;
						pre[P[i]]->opp->flow += Min;
						if(fabs(pre[P[i]]->flow) < 1e-6) top = i - 1;
					}
					u = P[top];
					flow += Min;
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
}G;

void init()
{
	scanf("%d%d%d", &n, &m, &e);
	G.clear(0, n+m+1);

	s = 0, t = n + m + 1;

	double a;
	for(int i=1; i<=n; ++i)
	{
		scanf("%lf", &a);
		G.addEdge(s, i, log(a));
	}
	for(int i=1; i<=m; ++i)
	{
		scanf("%lf", &a);
		G.addEdge(i+n, t, log(a));
	}
	int x, y;
	for(int i=0; i<e; ++i)
	{
		scanf("%d%d", &x, &y);
		G.addEdge(x, y+n, INF);
	}
}

void solve()
{
	double k = G.Dinic(s, t);
	printf("%.4lf\n", exp(k));
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

