#include <stdio.h>
#include <cstring>

double f[1010][110];
int n, m, c;

double solve()
{
	if(m > n || (n - m) & 1) return 0;
	if(m > c) return 0;

	memset(f, 0, sizeof f);
	f[0][0] = 1.0;

	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<=c; ++j)
		{
			if(j < c) f[i][j] += f[i-1][j+1] * (j + 1) / c;
			if(j) f[i][j] += f[i-1][j-1] * (c - j + 1) / c;
		}
	}

	return f[n][m];
}

int main()
{
	while(scanf("%d%d%d", &c, &n, &m) == 3)
	{
		printf("%.3lf\n", solve());
	}
	return 0;
}

