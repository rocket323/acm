#include <stdio.h>
#include <cstring>
#define maxl 210

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxl * 2];

char S[maxl][100], A[100], B[100];
int top, n, f[maxl][2], mset, p[maxl], c[maxl][2];

int max(int a, int b){ return (a>b)?a:b; }

int find(char t[])
{
	for(int i=0; i<top; ++i)
	{
		if(strcmp(S[i], t) == 0) return i;
	}
	strcpy(S[top++], t);
	return top - 1;
}

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void dp(int now)
{
	f[now][0] = 0, f[now][1] = 1;
	c[now][0] = c[now][1] = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] == k) continue;

		p[k] = now;
		dp(k);

		if(f[k][0] > f[k][1]){ f[now][0] += f[k][0]; c[now][0] *= c[k][0]; }
		if(f[k][0] < f[k][1]){ f[now][0] += f[k][1]; c[now][0] *= c[k][1]; }
		if(f[k][0] == f[k][1]){ f[now][0] += f[k][0]; c[now][0] = 0; }
		f[now][1] += f[k][0];
		c[now][1] *= c[k][0];
	}
}

void init()
{
	top = 1;
	scanf("%s", S[0]);
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=1; i<n; ++i)
	{
		scanf("%s%s", A, B);
		int a = find(A);
		int b = find(B);
		addEdge(b, a);
	}
}

int solve()
{
	memset(p, -1, sizeof p);
	dp(0);
	printf("%d ", max(f[0][0], f[0][1]));
	if(f[0][0] == f[0][1]) return 0;
	if(f[0][0] > f[0][1]) return c[0][0];
	if(f[0][0] < f[0][1]) return c[0][1];
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		init();
		int k = solve();
		if(k) puts("Yes");
		else puts("No");
	}
	return 0;
}


