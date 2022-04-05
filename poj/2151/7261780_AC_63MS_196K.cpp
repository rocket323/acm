#include <stdio.h>
#include <cstring>

double f[50][50], p[50], ans, zero;
int n, t, m;

int main()
{
	while(scanf("%d%d%d", &m, &t, &n), (m + t + n))
	{
		ans = 1.0; zero = 1.0;
		for(int x=0; x<t; ++x)
		{
			for(int i=1; i<=m; ++i) scanf("%lf", &p[i]);
			memset(f, 0, sizeof f);
			f[0][0] = 1.0;

			for(int i=1; i<=m; ++i)
			{
				for(int j=0; j<=i; ++j)
				{
					f[i][j] = f[i-1][j] * (1 - p[i]);
					if(j) f[i][j] += f[i-1][j-1] * p[i];
				}
			}

			zero *= (1.0 - f[m][0]);
			double tmp = 0.0;
			for(int i=1; i<n; ++i) tmp += f[m][i];
			ans *= tmp;
		}
		ans = 1.0 - ans - (1.0 - zero);
		printf("%.3lf\n", ans);
	}
	return 0;
}

