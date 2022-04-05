#include <stdio.h>
#include <cstring>
#define MaxL 1010

struct Edge
{
	int idx;
	Edge * next;
}
adj[MaxL], memo[MaxL * MaxL * 2];

int n, m, a, b, mset;
int C[MaxL], col[MaxL], id[MaxL], low[MaxL], lv, p[MaxL];
int mark[MaxL], flag;

void addEdge(int a, int b)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=0; i<m; ++i)
	{
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

int find(int x)
{
	if(p[x] == x) return x;
	else return p[x] = find(p[x]);
}

void unionSet(int a, int b)
{
	p[find(a)] = find(b);
}

void dfs(int now, int fth)
{
	id[now] = low[now] = lv++;
	mark[now] = 1;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;

		if(!mark[k])
		{
			dfs(k, now);
			if(low[k] < low[now]) low[now] = low[k];
			if(low[k] <= id[now]) unionSet(now, k);
		}
		else if(k != fth)
		{
			if(low[k] < low[now]) low[now] = low[k];
		}
	}
}

void check(int now, int root, int cl)
{
	col[now] = cl;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[k] != root) continue;
		if(col[k]==-1) check(k, root, cl^1);
		else if(col[k] == cl)
		{
			flag = 1;
			return;
		}
	}
}

void solve()
{
	for(int i=1; i<=n; ++i) p[i] = i;

	memset(C, 0, sizeof C);
	memset(mark, 0, sizeof mark);
	lv = 0;
	for(int i=1; i<=n; ++i)
	{
		if(!mark[i]) dfs(i, -1);
	}

	for(int i=1; i<=n; ++i) C[find(i)]++;

	memset(col, -1, sizeof col);
	int ans = 0;
	for(int i=1; i<=n; ++i)
	{
		if(p[i] != i) continue;
		flag = 0;
		check(i, i, 0);
		ans += (flag ^ 1) * C[i];
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n+m))
	{
		init();
		solve();
	}
	return 0;
}

