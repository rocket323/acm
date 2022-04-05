#include <stdio.h>
#include <cstring>
#define maxl 200

double p[maxl][maxl], f[maxl * 4][maxl];
int n, x;

void calc(int now, int l, int r)
{
	if(l < r)
	{
		int mid = (l + r) / 2;
		calc(now * 2, l, mid);
		calc(now * 2 + 1, mid + 1, r);

		for(int i=l; i<=mid; ++i)
			for(int j=mid+1; j<=r; ++j)
				f[now][i] += f[now * 2][i] * f[now * 2 + 1][j] * p[i][j];

		for(int i=mid+1; i<=r; ++i)
			for(int j=l; j<=mid; ++j)
				f[now][i] += f[now * 2 + 1][i] * f[now * 2][j] * p[i][j];
	}
	else f[now][l] = 1.0;
}

int main()
{
	while(scanf("%d", &x), (x + 1))
	{
		n = (1 << x);
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=n; ++j)
			{
				scanf("%lf", &p[i][j]);
			}
		}

		memset(f, 0, sizeof f);
		calc(1, 1, n);

		double pro = 0.0;
		int ans = -1;
		for(int i=1; i<=n; ++i) if(f[1][i] > pro) pro = f[1][i], ans = i;
		printf("%d\n", ans);
	}

	return 0;
}

