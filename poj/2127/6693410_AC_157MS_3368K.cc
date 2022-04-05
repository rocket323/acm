#include <stdio.h>
#include <cstring>
#define maxl 505

int n, m, f[maxl][maxl], a[maxl], b[maxl], mat[maxl], pa[maxl][maxl], pb[maxl][maxl];

void out(int na, int nb)
{
	if(pa[na][nb] == 0) printf("%d", a[na], b[nb]);
	else
	{
		out(pa[na][nb], pb[na][nb]);
		printf(" %d", a[na], b[nb]);
	}
}

void solve()
{
	int ans = 0, ra = -1, rb = -1;
	memset(f, 0, sizeof f);

	mat[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		int k = 0;
		for(int j=1; j<=m; ++j)
		{
			f[i][j] = f[i-1][j];
			if(a[i] > b[j] && f[i][k] < f[i][j]) k = j;
			if(a[i] == b[j] && f[i][k] + 1 > f[i][j])
			{
				f[i][j] = f[i][k] + 1;
				pa[i][j] = mat[k];
				pb[i][j] = k;
				mat[j] = i;
			}

			//printf("%d %d %d %d %d\n", i, j, k, mat[k], f[i][j]);

			if(f[i][j] > ans)
			{
				ra = i;
				rb = j;
				ans = f[i][j];
			}
		}
	}

	printf("%d\n", ans);
	if(ans)
	{
		out(ra, rb);
		puts("");
	}
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i=1; i<=m; ++i) scanf("%d", &b[i]);

	solve();

	return 0;
}

