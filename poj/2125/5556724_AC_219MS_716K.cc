#include <stdio.h>
#include <cstring>
#define MaxL 310
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

struct Edge
{
	int idx, flow;
	Edge *next, *opp;
}
adj[MaxL], memo[MaxL * MaxL];

int vis[MaxL];
int n, m, mset, s, t, tank;
int Q[MaxL], head, tail, lv[MaxL];
char g[MaxL][MaxL];
Edge * pre[MaxL];
int R[MaxL], rt, C[MaxL], ct;

void addEdgeProcess(int a, int b, int c)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->flow = c;
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
	s = 0, t = n + n + 1;

	mset = 0;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;

	int w;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &w);
		addEdge(i+n, t, w);
	}
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &w);
		addEdge(s, i, w);
	}

	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b+n, INF);
	}
}

bool bfs(int s, int t)
{
	memset(lv, 0, sizeof lv);
	lv[s] = 1;
	Q[head = 0] = s;
	tail = 1;

	while(head < tail)
	{
		int k = Q[head];
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			if(ptr->flow && !lv[ptr->idx])
			{
				pre[ptr->idx] = ptr;
				Q[tail++] = ptr->idx;
				lv[ptr->idx] = 1;
			}
		}
		head++;
	}

	return lv[t] != 0;
}

int max_flow(int s, int t)
{
	int ans = 0;

	while(bfs(s, t))
	{
		int k = t, Min = INF;
		while(k != s)
		{
			Min = min(Min, pre[k]->flow);
			k = pre[k]->opp->idx;
		}
		ans += Min;
		k = t;
		while(k != s)
		{
			pre[k]->flow -= Min;
			pre[k]->opp->flow += Min;
			k = pre[k]->opp->idx;
		}
	}
	return ans;
}

void dfs(int now)
{
	vis[now] = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		if(!vis[ptr->idx] && ptr->flow) dfs(ptr->idx);
	}
}

void out(int a[], int top)
{
	for(int i=0; i<top; ++i) printf(" %d", a[i]);
	puts("");
}

void solve()
{
	int k = max_flow(s, t);

	printf("%d\n", k);

	memset(vis, 0, sizeof vis);
	dfs(s);
	
	rt = ct = 0;
	for(int i=1; i<=n; ++i) if(!vis[i]) R[rt++] = i;
	for(int i=1; i<=n; ++i) if(vis[i+n]) C[ct++] = i;
	
	printf("%d\n", rt+ct);
	for(int i=0; i<rt; ++i) printf("%d -\n", R[i]);
	for(int i=0; i<ct; ++i) printf("%d +\n", C[i]);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

