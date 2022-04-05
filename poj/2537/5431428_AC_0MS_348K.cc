#include <stdio.h>
#include <cstring>

int n, k;
double f[101][10];

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1.0;

	double ans = 0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<=k; ++j)
		{
			if(i==1) f[i][j] = 1.0 / (k + 1);
			else
			{
				f[i][j] = f[i-1][j] * 1.0 / (k + 1);
				if(j > 0) f[i][j] += f[i-1][j-1] * 1.0 / (k + 1);
				if(j < k) f[i][j] += f[i-1][j+1] * 1.0 / (k + 1);
			}
			if(i==n) ans += f[i][j];
		}
	}
	printf("%.5f\n", ans * 100);
}

int main()
{
	while(scanf("%d%d", &k, &n) != EOF) solve();
	return 0;
}
