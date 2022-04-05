#include <stdio.h>
#include <cstring>
#define MaxL 520
#define INF 10000000

struct Edge
{
	int idx, flow;
	Edge * next;
	Edge * opp;
}adj[MaxL], memo[20100];

int g[MaxL][MaxL];
int n, m, s, t, mset;
int Q[MaxL], head, tail;
int P[MaxL], lv[MaxL];
int S[MaxL], sz, top, del[MaxL];
Edge *cur[MaxL], *pre[MaxL];

void addEdgeProcess(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->flow = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c)
{
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp = &memo[mset-1];
	adj[b].next->opp = &memo[mset-2];
}

void build_Gra()
{
	mset = 0;
	for(int i=1; i<=2*n; ++i) adj[i].next = NULL;
	
	for(int i=1; i<=n; ++i)
	{
		if(del[i] || i==s || i==t) continue;
		addEdge(i, i+n, 1);
	}
	
	for(int i=1; i<=n; ++i)
	{
		if(i==s || i==t) continue;
		for(int j=i+1; j<=n; ++j)
		{
			if(del[i] || del[j]) continue;
			if(g[i][j])
			{
				addEdge(i+n, j, 1);
				addEdge(j+n, i, 1);
			}
		}
	}
	for(int j=1; j<=n; ++j) if(!del[j]) addEdge(s, j, INF);
	for(int j=1; j<=n; ++j) if(!del[j]) addEdge(j+n, t, INF);
}

void init()
{
	memset(del, 0, sizeof del);
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) scanf("%d", &g[i][j]);
	build_Gra();
}

int bfs(int s, int t)
{
	memset(lv, -1, sizeof lv);
	tail = 1;
	Q[head = 0] = s; lv[s] = 0;
	
	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(lv[ptr->idx]==-1 && ptr->flow>0)
			{
				Q[tail++] = ptr->idx;
				lv[ptr->idx] = lv[k] + 1;
			}
		}
		head++;
	}
	return lv[t] != -1;
}

int min(int a, int b){ return (a<b)?a:b; }

int max_flow(int s, int t)
{
	int flow = 0, u;
	while(bfs(s, t))
	{
		P[top = 1] = u = s;
		for(int i=1; i<=2*n; ++i) cur[i] = adj[i].next;
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
				int Min = INF;
				for(int i=top; i>1; --i) Min = min(Min, pre[P[i]]->flow);
				for(int i=top; i>1; --i)
				{
					pre[P[i]]->flow -= Min;
					pre[P[i]]->opp->flow += Min;
					if(pre[P[i]]->flow==0) top = i-1;
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

void out()
{
	printf("%d\n", sz);
	if(top)
	{
		for(int i=1; i<sz; ++i) printf("%d ", S[i]);
		printf("%d\n", S[sz]);
	}
}

void solve()
{
	sz = 0;
	int flow = max_flow(s, t);
	
	
	
	for(int i=1; i<=n; ++i)
	{
		if(i==s || i==t) continue;
		del[i] = 1;
		build_Gra();
		int k = max_flow(s, t);
		if(k < flow){
			S[++sz] = i; flow = k;
		}
		else del[i] = 0;
	}

	if(flow > 0) printf("NO ANSWER!\n");
	else out();

}

int main()
{
	while(scanf("%d%d%d", &n, &s, &t)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
