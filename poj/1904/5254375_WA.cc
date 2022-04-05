#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define UNVIS 0
#define VIS 1
#define OVER 2
#define MaxL 4010

struct Edge
{
	int idx;
	Edge *next;
}
adj[MaxL], memo[300010];

int n, mset;
int S[MaxL], mark[MaxL], id[MaxL], low[MaxL], lv, sz;
int A[MaxL], pre[MaxL], lx[MaxL], ly[MaxL];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	int k, a;
	mset = 0;
	for(int i=0; i<=2*n; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &k);
		for(int j=0; j<k; ++j)
		{
			scanf("%d", &a);
			addEdge(i, a + n);
		}
	}
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a);
		addEdge(a + n, i);
		lx[i] = a;
		ly[a] = i;
	}
}

void dfs(int now)
{
	S[++sz] = now;
	id[now] = low[now] = lv++;
	mark[now] = VIS;
	
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
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
	}
	if(low[now]==id[now])
	{
		do
		{
			pre[S[sz]] = now;
			mark[S[sz]] = OVER;
		}while(S[sz--]!=now);
	}
}

void tarjan()
{
	sz = lv = 0;
	memset(mark, 0, sizeof mark);
	for(int i=1; i<=2*n; ++i)
	{
		if(mark[i]==UNVIS) dfs(i);
	}
}

void solve()
{
	tarjan();
	for(int i=1; i<=n; ++i)
	{
		int cnt = 0;
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			int k = ptr->idx;
			if(pre[lx[i]]==pre[ly[k-n]]) A[++cnt] = k - n;
		}
		sort(A+1, A+1+cnt);
		printf("%d ", cnt);
		for(int j=1; j<cnt; ++j) printf("%d ", A[j]);
		printf("%d\n", A[cnt]);
	}
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
