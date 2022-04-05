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
int ans[MaxL];
int vis[MaxL], list[MaxL * MaxL * 2], sz;
int E1[MaxL * MaxL * 2], E2[MaxL * MaxL * 2], top, bc, B[MaxL];

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
		//g[a][b] = g[b][a] = 1;
		addEdge(a, b);
		addEdge(b, a);
	}
/*
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
			if(g[i][j]==0 && i!=j) addEdge(i, j);
	}
*/
}

void check(int now, int BCC, int cl)
{
	col[now] = cl;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(!vis[k]) continue;
		if(col[k]==-1) check(k, BCC, cl^1);
		else if(col[k] == cl)
		{
			flag = 1;
			return;
		}
	}
}

void dfs(int now, int fth)
{
	id[now] = low[now] = lv++;
	mark[now] = 1;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		
		if(k != fth && id[now] > id[k])
		{
			++top;
			E1[top] = now, E2[top] = k;
		}

		if(!mark[k])
		{
			dfs(k, now);
			if(low[k] < low[now]) low[now] = low[k];

			if(low[k] >= id[now])
			{
				bc++;
				int x, y;
				do
				{
					x = E1[top];
					y = E2[top];
					vis[x] = vis[y] = 1;
					col[x] = col[y] = -1;
					list[sz++] = x;
					list[sz++] = y;
					top--;
				}
				while(!(x==now && y==k)); 
				flag = 0;

				check(now, bc, 0);

				if(flag)
				{
					for(int i=0; i<sz; ++i) ans[list[i]] |= vis[list[i]];
				}

				for(int i=0; i<sz; ++i) vis[list[i]] = 0;
				sz = 0;
				
			}

		}
		else if(k != fth)
		{
			if(id[k] < low[now]) low[now] = id[k];
		}
	}
}

void solve(int ct)
{
	memset(mark, 0, sizeof mark);
	memset(ans, 0, sizeof ans);
	memset(col, -1, sizeof col);
	memset(id, -1, sizeof id);
	lv = bc = 0;
	sz = 0;
	for(int i=1; i<=n; ++i)
	{
		if(!mark[i]) dfs(i, -1);
	}

	int ret = 0;
	for(int i=1; i<=n; ++i)
		if(!ans[i]) ret++;
	printf("%d\n", ret);
}

int main()
{
	int t = 0;
	while(scanf("%d%d", &n, &m) && (n+m))
	{
		init();
		solve(++t);
	}
	return 0;
}


