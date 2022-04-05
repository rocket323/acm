#include <stdio.h>
#include <cstring>
#define maxl 210
#define sqr(x) ((x) * (x))

int c[maxl], a[maxl], cnt[maxl], n, m;
int f[maxl][maxl][maxl], pre[maxl], sum[maxl];

int max(int a, int b){ return (a>b)?a:b; }

void init()
{
	scanf("%d", &m);
	for(int i=1; i<=m; ++i) scanf("%d", &c[i]);

	n = 0;
	for(int i=1; i<=m; ++i)
	{
		if(n == 0 || c[i] != a[n])
		{
			n++;
			cnt[n] = 1;
			a[n] = c[i];
		}
		else cnt[n]++;
	}

	memset(pre, -1, sizeof pre);
	for(int i=1; i<=n; ++i)
	{
		for(int j=i-1; j>=1; --j)
		{
			if(a[i] == a[j])
			{
				pre[i] = j;
				break;
			}
		}
		sum[i] = 0;
		for(int j=i+1; j<=n; ++j)
		{
			if(a[j] == a[i]) sum[i] += cnt[j];
		}
	}
}

void solve()
{

	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<=m; ++j) f[i][i][j] = sqr(cnt[i] + j);
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(int k=0; k<=sum[j]; ++k)
			{
				f[i][j][k] = f[i][j-1][0] + sqr(cnt[j] + k);
				for(int p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = max(f[i][j][k], f[i][p][k+cnt[j]] + f[p+1][j-1][0]);
				}
			}
		}
	}
	printf("%d\n", f[1][n][0]);
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int i=1; i<=t; ++i)
	{
		init();
		printf("Case %d: ", i);
		solve();
	}
	return 0;
}

