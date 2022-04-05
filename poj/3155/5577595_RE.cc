#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define MaxL 103
#define MaxE 3000
#define ZERO 1e-6

int n, m, s, t;
int A[MaxL], top, tmp[MaxL], ttop;
int degree[MaxL];
int vis[MaxL];

struct Graph
{
	struct Edge
	{
		int idx, flag;
		double flow;
		Edge *next, *opp;
	}
	adj[MaxL], memo[MaxE];

	int mset, Q[MaxL], head, tail, lv[MaxL], P[MaxL], top, low, up;
	Edge *pre[MaxL], *cur[MaxL];

	void clear(int l, int u){ mset = 0; low = l, up = u;  for(int i=l; i<=u; ++i) adj[i].next = NULL; }

	void addEdgeProcess(int a, int b, int c, int flag)
	{
		Edge *ptr = &memo[mset++];
		ptr->idx = b; ptr->flow = c;
		ptr->flag = flag;
		ptr->next = adj[a].next;
		adj[a].next = ptr;
	}

	void addEdge(int a, int b, int c, int flag)
	{
		addEdgeProcess(a, b, c, flag);
		addEdgeProcess(b, a, 0, 0);
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
				if(ptr->flow > 0 && lv[ptr->idx]==-1)
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
		int u;
		double flow = 0;
		while(bfs(s, t))
		{
			P[top = 1] = u = s;
			for(int i=low; i<=up; ++i) cur[i] = adj[i].next;
			while(cur[s])
			{
				if(u!=t && cur[u] && cur[u]->flow>0 && lv[cur[u]->idx]==lv[u]+1)
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
						if(fabs(pre[P[i]]->flow)<ZERO) top = i - 1;
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

	void rebuild(double g, int s, int t)
	{
		for(Edge *ptr=adj[s].next; ptr; ptr=ptr->next)
		{
			ptr->flow = m;
			ptr->opp->flow = 0;
		}

		for(Edge *ptr=adj[t].next; ptr; ptr=ptr->next)
		{
			ptr->opp->flow = m + 2 * g - degree[ptr->idx];
			ptr->flow = 0;
		}

		for(int i=1; i<=n; ++i)
		{
			for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
			{
				if(ptr->flag == 0) continue;
				ptr->flow = 1;
			}
		}
	}

	void findNode(int now)
	{
		vis[now] = 1;
		tmp[ttop++] = now;
		for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
		{
			if(ptr->flow > 0 && !vis[ptr->idx]) findNode(ptr->idx);
		}
	}
	
}G;

void init()
{
	s = 0, t = n + 1;
	G.clear(s, t);
	memset(degree, 0, sizeof degree);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		G.addEdge(a, b, 1, 1);
		G.addEdge(b, a, 1, 1);
		degree[a]++;
		degree[b]++;
	}
	for(int i=1; i<=n; ++i)
	{
		G.addEdge(s, i, m, 0);
		G.addEdge(i, t, 0, 0);
	}
}

void solve()
{
	double l = 0, r = m, ans = 0, mid, eps = 1e-4;

	top = 2; A[1] = 1;

	while(l <= r + eps)
	{
		mid = (l + r) / 2.0;
		G.rebuild(mid, s, t);
		G.Dinic(s, t);

		memset(vis, 0, sizeof vis);
		ttop = 0;
		G.findNode(s);
		if(ttop > 1)
		{
			ans = mid;
			top = ttop;
			for(int i=0; i<ttop; ++i) A[i] = tmp[i];
			l = mid + eps;
		}
		else r = mid - eps;
	}
	sort(A, A+top);
	printf("%d\n", top-1);
	for(int i=1; i<top; ++i) printf("%d\n", A[i]);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		solve();
	}
}
