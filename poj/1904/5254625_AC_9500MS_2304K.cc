/*
	POJ1904
	求二分图的所有可能匹配边(i,j)，即删除i，j后剩下的图还是构成一个完全匹配
	
	以下：lx[i]表示初始匹配中与第i个王子匹配的公主，ly[j]表示初始匹配中与第j个公主匹配的王子
	
	暴力做法：对于每条边(i,j)，删除i，j后如果可以从ly[j]开始找到一条增广路，则(i,j)是一条符合条件的边
	
	进一步分析：(i,j)符合条件的充要条件是：删除i，j后，可以从ly[j]到lx[i]找到一条增广路(有向)，而原图中存在边(lx[i],i), (i,j), (j,ly[j]),就是ly[j]与lx[i]在同一个
	强连通分量内。利用这个充要条件就可以判断(i,j)是否符合条件了。
	
	程序步骤：
		1)对二分图中的边定向，不是初始匹配的边(i,j)从i 连到j ，初始匹配的边(i,j)从j 连到i。
		2)对建出来的图求强连通分量。
		3)对于二分图中的每一条边(i,j)如果ly[j], lx[i] 在同一强连通分量中，则(i,j)为符合条件的边。
		4)对边排序输出。
*/


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
		lx[i] = a + n;
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

void out(int A[], int len)
{
	sort(A+1, A+1+len);
	printf("%d ", len);
	for(int j=1; j<len; ++j) printf("%d ", A[j]);
	printf("%d\n", A[len]);
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
		out(A, cnt);
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
