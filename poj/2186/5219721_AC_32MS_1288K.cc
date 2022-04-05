#include <stdio.h>
#include <cstring>
#define MaxL 10010
#define UNVIS 0
#define VIS 1
#define OVER 2

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[5*MaxL];

int n, m, mset;
int pre[MaxL], d[MaxL], C[MaxL];
int S[MaxL], id[MaxL], low[MaxL], mark[MaxL], lv, sz;

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
}

void dfs(int now)
{
	id[now] = low[now] = lv++;
	S[++sz] = now; mark[now] = VIS;
	Edge * ptr = adj[now].next;


	while(ptr)
	{
		int k = ptr->idx;
		if(mark[k]==UNVIS)
		{
			dfs(k);
			if(low[k]<low[now]) low[now] = low[k];
		}
		else if(mark[k]==VIS)
		{
			if(low[k]<low[now]) low[now] = low[k];
		}
		ptr = ptr->next;
	}
	if(low[now]==id[now])
	{
		C[now] = 0;
		do
		{
			C[now]++;
			pre[S[sz]] = now;
			mark[S[sz]] = OVER;
		}while(S[sz--]!=now);
	}
}

void make_Gra()
{
	memset(d, 0, sizeof d);
	for(int i=1; i<=n; ++i)
	{
		Edge * ptr = adj[i].next;
		while(ptr)
		{
			int k = ptr->idx;
			if(pre[i]!=pre[k]) d[pre[i]]++;
			ptr = ptr->next;
		}
	}
}

void solve()
{
	int cnt = 0, ans = 0;
	lv = sz = 0;
	memset(mark, 0, sizeof mark);
	for(int i=1; i<=n; ++i)
	{
		if(mark[i]==UNVIS) dfs(i);
	}


	make_Gra();
	for(int i=1; i<=n; ++i)
	{
		if(pre[i]!=i || d[i]!=0) continue;
		cnt++;
		ans = C[i];
	}
	if(cnt > 1) printf("0\n");
	else printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	init();
	solve();
	return 0;
}
