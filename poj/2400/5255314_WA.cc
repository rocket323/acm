#include <stdio.h>
#include <cstring>
#define MaxL 16
#define INF 0x7f7f7f7f

struct node
{
	int mat[MaxL];
}Q[10000];

int l1[MaxL][MaxL], l2[MaxL][MaxL];
int vis[MaxL], top, A[MaxL][MaxL], B[MaxL][MaxL];
int mat[MaxL], Min, n;

void init()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			scanf("%d", &l1[i][j]);
			A[i][l1[i][j]] = j;
		}
	}
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			scanf("%d", &l2[i][j]);
			B[i][l2[i][j]] = j;
		}
	}
	
}

void dfs(int now, int sum)
{
	if(sum > Min) return;
	
	if(now==n+1)
	{
		if(sum < Min) Min = sum, top = 1;
		else top++;
		for(int i=1; i<=n; ++i) Q[top].mat[i] = mat[i];
		return;
	}
	
	for(int i=1; i<=n; ++i)
	{
		int k = l1[now][i-1];
		if(vis[k]) continue;
		vis[k] = 1;
		mat[now] = k;
		dfs(now + 1, sum + A[now][k] + B[k][now]);
		vis[k] = 0;
	}
}

void solve(int cas)
{
	memset(vis, 0, sizeof vis);
	Min = INF;
	top = 0;
	dfs(1, 0);
	
	printf("Data Set %d, Best average difference: %.6f\n", cas, Min * 1.0 / 2 / n);
	for(int i=1; i<=top; ++i)
	{
		printf("Best Pairing %d\n", i);
		for(int j=1; j<=n; ++j) printf("Supervisor %d with Employee %d\n", j, Q[i].mat[j]);
	}
	printf("\n");
}

int main()
{
	int t, cnt = 0;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve(++cnt);
	}
	return 0;
}
