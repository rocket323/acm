#include <stdio.h>
#include <cstring>
#define MaxL 101
#define max(a,b) ((a>b)?a:b)

int f[MaxL][MaxL], n, m, a[MaxL], b[MaxL];

void init()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	for(int i=1; i<=m; ++i) scanf("%d", &b[i]);
	memset(f, 0, sizeof f);
}

int go(int a[], int x, int p)
{
	for(int i=p-1; i>=1; --i)
	{
		if(a[i]==x) return i;
	}
	return -1;
}

void solve()
{
	int ans = 0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			f[i][j] = 0;
			f[i][j] = max(f[i][j], f[i-1][j-1]);
			f[i][j] = max(f[i][j], f[i-1][j]);
			f[i][j] = max(f[i][j], f[i][j-1]);

			if(a[i]==b[j]) continue;
			int p1 = go(a, b[j], i);
			int p2 = go(b, a[i], j);
			if(p1!=-1 && p2!=-1)
			{
				f[i][j] = max(f[i][j], f[p1-1][p2-1] + 2);
				ans = max(ans, f[i][j]);
			}
		}
	}
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

