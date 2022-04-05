#include <stdio.h>
#include <cstring>
#define INF 0x3f7f7f7f
#define MaxL 5010
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, flow;
	Edge *next, *opp;
}
adj[MaxL], memo[140000];

int mset, n, m, s, t, w[MaxL], in[MaxL];
long long psum;
int Q[MaxL], head, tail, lv[MaxL], P[MaxL], top;
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

void init()
{
	scanf("%d%d", &n, &m);
	s = 0, t = n + 1;
	mset = 0;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &w[i]);
		psum += w[i] * (w[i] > 0);
	}
	for(int i=1; i<=m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b, INF);
	}
	for(int i=1; i<=n; ++i) 
	{
		if(w[i] > 0) addEdge(s, i, w[i]);
		else if(w[i] < 0) addEdge(i, t, -w[i]);
	}
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

long long Dicnic(int s, int t)
{
	long long flow = 0;
	int u;
	while(bfs(s, t))
	{
		P[top = 1] = u = s;
		for(int i=s; i<=t; ++i) cur[i] = adj[i].next;
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

void dfs(int now)
{
	in[now] = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		if(ptr->flow>0 && !in[ptr->idx]) dfs(ptr->idx);
	}
}

void solve()
{
	long long k = Dicnic(s, t);
	memset(in, 0, sizeof in);
	dfs(s);
	int cnt = 0;
	for(int i=1; i<=n; ++i)
	{
		if(i!=s && in[i]) cnt++;
	}
	printf("%d %I64d\n", cnt, psum-k);
}

int main()
{
	init();
	solve();
	return 0;
}
