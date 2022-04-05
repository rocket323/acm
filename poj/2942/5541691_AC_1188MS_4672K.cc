#include <stdio.h>
#include <cstring>
#define MaxL 1010

struct Edge
{
	int idx;
	Edge * next;
}
adj[MaxL], memo[MaxL * MaxL * 10];

int n, m, a, b, mset;
int g[MaxL][MaxL];
int C[MaxL], col[MaxL], id[MaxL], low[MaxL], lv, p[MaxL];
int mark[MaxL], flag;
int ans[MaxL];
int vis[MaxL];
int E1[MaxL * MaxL * 10], E2[MaxL * MaxL * 10], top, bc, B[MaxL];

void addEdge(int a, int b)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;

	//if(a <= b) printf("%d %d\n", a, b);
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

int find(int x)
{
	if(p[x] == x) return x;
	else return p[x] = find(p[x]);
}

void unionSet(int a, int b)
{
	p[find(a)] = find(b);
}


void check(int now, int BCC, int cl)
{
	//int flag = 0;
	col[now] = cl;

	//if(BCC==2) printf("h %d %d\n", now, col[now]);

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		//if(B[k] != BCC) continue;
		if(!vis[k]) continue;
		if(col[k]==-1) check(k, BCC, cl^1);
		else if(col[k] == cl)
		{
			flag = 1;
			return;
		}
	}
	//if(flag) ans[now] = 1;
}

void out()
{
	puts("\n*****************");
	for(int i=top; i>=1; --i)
	{
		printf("%d %d\n", E1[i], E2[i]);
	}
	puts("\n*****************");
}

void dfs(int now, int fth)
{
	id[now] = low[now] = lv++;
	mark[now] = 1;

	//printf("%d\n", now);

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
				//out();
				//printf("now %d : ", now);
				//printf("1");
				memset(vis, 0, sizeof vis);
				do
				{
					//if(top <= 0) break;
					x = E1[top];
					y = E2[top];
					B[x] = B[y] = bc;
					vis[x] = vis[y] = 1;
					col[x] = col[y] = -1;
					top--;
					//printf("%d %d ", x, y);
				}
				while(!(x==now && y==k)); 
				//puts("");
				//printf("2");

				//for(int i=1; i<=n; ++i) printf("%d ", B[i]);
				//puts("");
				flag = 0;

				memset(col, -1, sizeof col);
				check(now, bc, 0);

				if(flag)
				{
					for(int i=1; i<=n; ++i) ans[i] |= vis[i];
				}
				
			}

		}
		else if(k != fth)
		{
			if(id[k] < low[now]) low[now] = id[k];
		}
	}
	//printf("%d %d %d\n", now, id[now], low[now]);
}

void solve(int ct)
{
	for(int i=1; i<=n; ++i) p[i] = i;

	memset(C, 0, sizeof C);
	memset(mark, 0, sizeof mark);
	memset(ans, 0, sizeof ans);
	memset(col, -1, sizeof col);
	memset(id, -1, sizeof id);
	lv = bc = 0;
	for(int i=1; i<=n; ++i)
	{
		if(!mark[i])
		{
			//++top;
			//E1[top] = i;
			//E1[top] = -1;
			dfs(i, -1);
		}
	}

	int ret = 0;
	for(int i=1; i<=n; ++i)
		if(!ans[i]) ret++;
	printf("%d\n", ret);
/*
	for(int i=1; i<=n; ++i) C[find(i)]++;

	//for(int i=1; i<=n; ++i) printf("%d %d\n", i, find(i));
	if(ct==1)
	for(int i=1; i<=n; ++i)
	{
		printf("%d\n", C[i]);
	}
	int an = 0, cnt = 0;
	for(int i=1; i<=n; ++i)
	{
		if(p[i] != i) continue;
		flag = 0;
		check(i, i, 0);

		if(ct==1) cnt++;
		//if(ct==1)
		//	printf("%d %d %d\n", i, flag, C[i]);
		an += (flag ^ 1) * C[i];
		ans[i] = flag^1;
	}

	//if(ct==1) printf("%d %d\n", cnt, an);
	printf("%d\n", an);
*/
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

