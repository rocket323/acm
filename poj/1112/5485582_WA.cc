#include <stdio.h>
#include <cstring>
#define MaxL 101

int g[MaxL][MaxL], adj[MaxL][MaxL], k;
int flag, n;
int col[MaxL], dep[MaxL];
int zero[MaxL], one[MaxL], top;
int p[MaxL][MaxL];

int group[MaxL];
int s1[MaxL], sz1, s2[MaxL], sz2;

int f[MaxL][200], pre[MaxL][MaxL];

void dfs(int now, int cl, int dp)
{
	col[now] = cl, dep[now] = dp;
	if(dp==0) zero[cl]++;
	else one[cl]++;

	for(int i=1; i<=n; ++i)
	{
		if(i!=now && col[i]==-1) dfs(i, cl, dp^1);
	}
}

void init()
{
	memset(g, 0, sizeof g);
	for(int i=1; i<=n; ++i)
	{
		while(scanf("%d", &k) && k) g[i][k] = 1;
	}
	flag = 1;
	top = 0;

	memset(col, -1, sizeof col);
	for(int i=1; i<=n; ++i)
	{
		if(col[i]==-1) dfs(i, ++top, 0);
		if(!flag) break;
	}
}

void out(int a[], int len)
{
	printf("%d ", len);
	for(int i=1; i<len; ++i) printf("%d ", a[i]);
	printf("%d\n", a[len]);
}

void solve()
{
	if(!flag)
	{
		printf("No solution\n");
		return;
	}

	memset(f, 0, sizeof f);
	f[0][0] = 1;

	for(int i=0; i<top; ++i)
	{
		for(int j=0; j<=n; ++j)
		{
			if(f[i][j]==0) continue;

			f[i+1][j+zero[i+1]] = 1;
			p[i+1][j+zero[i+1]] = j;

			f[i+1][j+one[i+1]] = 1;
			p[i+1][j+one[i+1]] = j;
		}
	}
	int k = 0;
	for(int i=1; i<=n/2; ++i)
	{
		if(f[top][i])
		{
			k = i;
			break;
		}
	}

	if(k==0)
	{
		printf("No solution\n");
		return;
	}

	sz1 = sz2 = 0;
	for(int i=top; i>=1; --i)
	{
		if(k - p[i][k] == zero[i])
		{
			for(int j=1; j<=n; ++j)
			{
				if(col[j]!=i) continue;
				
				if(dep[j]==0) s1[++sz1] = j;
				else s2[++sz2] = j;
			}
		}
		else
		{
			for(int j=1; j<=n; ++j)
			{
				if(col[j]!=i) continue;

				if(dep[j]==0) s2[++sz2] = j;
				else s1[++sz1] = j;
			}
		}
		k = p[i][k];
	}

	out(s1, sz1);
	out(s2, sz2);
	
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
