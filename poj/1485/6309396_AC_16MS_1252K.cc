#include <stdio.h>
#include <cstring>
#define maxl 210
#define INF 0x3f3f3f3f

int sum[maxl], w[maxl][maxl], r[maxl][maxl], ss[maxl];
int n, m, d[maxl], f[maxl][maxl];
int p[maxl][maxl];

int calc(int p, int i, int j)
{
	return (p - i - j + p) * d[p] - (sum[p-1] - sum[i-1]) + (sum[j] - sum[p]);
}

void init()
{
	sum[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &d[i]);
		sum[i] = sum[i-1] + d[i];
	}

	for(int i=1; i<=n; ++i)
	{
		int p = i;
		for(int j=i; j<=n; ++j)
		{
			r[i][j] = (i + j) / 2;
			w[i][j] = calc(r[i][j], i, j);
		}
	}
}

void out(int n, int m)
{
	if(n == 0) return;
	out(p[n][m], m-1);
	int k = n - p[n][m];
	if(k > 1) printf("Depot %d at restaurant %d serves restaurants %d to %d\n", m, r[p[n][m]+1][n], p[n][m] + 1, n);
	else printf("Depot %d at restaurant %d serves restaurant %d to %d\n", m, r[p[n][m]+1][n], p[n][m] + 1, n);
}

void solve()
{
	memset(f, 0x3f, sizeof f);

	f[0][0] = 0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			for(int k=0; k<i; ++k)
			{
				int tmp = f[k][j-1] + w[k+1][i];
				if(tmp < f[i][j])
				{
					f[i][j] = tmp;
					p[i][j] = k;
				}
			}
		}
	}

	out(n, m);
	printf("Total distance sum = %d\n", f[n][m]);
}

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m) && n)
	{
		printf("Chain %d\n", ++tc);
		init();
		solve();
		puts("");
	}
	return 0;
}

