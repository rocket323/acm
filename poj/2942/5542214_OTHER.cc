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
int g[MaxL][MaxL];
int col[MaxL], id[MaxL], low[MaxL], lv, p[MaxL];
int mark[MaxL];
int ans[MaxL];
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
	memset(g, 0, sizeof g);

	for(int i=0; i<m; ++i)
	{
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
			if(g[i][j]==0 && i!=j) addEdge(i, j);
	}
}

bool check(int now, int BCC, int cl)
{
	col[now] = cl;

	int flag = 0;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(B[k]!=BCC) continue;
		if(col[k]==-1) flag |= check(k, BCC, cl^1);
		else if(col[k] == cl)
		{
			flag = 1;
		}
	}
	if(flag) ans[now] = 1;
	return flag;
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
					B[x] = B[y] = bc;
					col[x] = col[y] = -1;
					top--;
				}
				while(!(x==now && y==k)); 

				check(now, bc, 0);
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
	memset(B, -1, sizeof B);
	lv = bc = 0;
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

