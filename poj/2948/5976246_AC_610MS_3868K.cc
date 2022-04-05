#include <stdio.h>
#include <cstring>
#define MaxL 520
#define max(a,b) ((a>b)?a:b)

int n, m, f[MaxL][MaxL], a_y[MaxL][MaxL], a_b[MaxL][MaxL], s_y[MaxL][MaxL], s_b[MaxL][MaxL];

void init()
{
	for(int i=1; i<=n; ++i)
	{
		s_y[i][0] = 0;
		for(int j=1; j<=m; ++j)
		{
			scanf("%d", &a_y[i][j]);
			s_y[i][j] = s_y[i][j-1] + a_y[i][j];
		}
	}
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j) scanf("%d", &a_b[i][j]);
	}
	for(int i=1; i<=m; ++i)
	{
		s_b[i][0] = 0;
		for(int j=1; j<=n; ++j) s_b[i][j] = s_b[i][j-1] + a_b[j][i];
	}
}

void solve()
{
	memset(f, 0, sizeof f);

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			f[i][j] = max(f[i][j], f[i][j-1] + s_b[j][i]);
			f[i][j] = max(f[i][j], f[i-1][j] + s_y[i][j]);
		}
	}
	printf("%d\n", f[n][m]);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n + m))
	{
		init();
		solve();
	}
	return 0;
}

