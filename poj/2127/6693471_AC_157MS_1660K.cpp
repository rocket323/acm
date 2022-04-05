#include <stdio.h>
#include <cstring>
#define maxl 505

short n, m, f[maxl][maxl], mat[maxl], pa[maxl][maxl], pb[maxl][maxl];
int a[maxl], b[maxl];

void out(short na, short nb)
{
	if(pa[na][nb] == 0) printf("%d", a[na]);
	else
	{
		out(pa[na][nb], pb[na][nb]);
		printf(" %d", a[na]);
	}
}

void solve()
{
	short ans = 0, ra = -1, rb = -1;
	for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j) f[i][j] = 0;

	mat[0] = 0;
	for(short i=1; i<=n; ++i)
	{
		short k = 0;
		for(short j=1; j<=m; ++j)
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
	for(short i=1; i<=n; ++i) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(short i=1; i<=m; ++i) scanf("%d", &b[i]);

	solve();

	return 0;
}

