#include <stdio.h>
#include <cstring>
#define maxl 520
#define min(a,b) ((a<b)?a:b)

int n, m, a[maxl], sum[maxl], f[maxl][maxl];
int p[maxl][maxl];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void out(int pos, int m)
{
	if(p[pos][m] == n)
	{
		for(int i=pos; i<n-1; ++i) printf("%d ", a[i]);
		printf("%d\n", a[n-1]);
	}
	else
	{
		for(int i=pos; i<p[pos][m]; ++i) printf("%d ", a[i]);
		printf("/ ");
		out(p[pos][m], m-1);
	}
}

void solve()
{
	scanf("%d%d", &n, &m);
	for(int i=0; i<n; ++i) scanf("%d", &a[i]);

	sum[n] = 0;
	for(int i=n-1; i>=0; --i) sum[i] = sum[i+1] + a[i];

	memset(f, 0x3f, sizeof f);
	f[n][0] = 0;

	for(int i=n-1; i>=0; --i)
	{
		for(int j=1; j<=m; ++j)
		{
			for(int k=i+1; k<=n; ++k)
			{
				int tmp = max(sum[i] - sum[k], f[k][j-1]);
				if(tmp < f[i][j])
				{
					f[i][j] = tmp;
					p[i][j] = k;
				}
			}
		}
	}
	out(0, m);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}

