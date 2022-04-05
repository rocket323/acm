#include <stdio.h>
#include <cstring>
#include <math.h>
#define eps (1e-8)
#define maxl 100

char str[20];
int n, m, a[maxl], L[maxl];
double f[maxl][maxl];

void go(int i, int j, int k)
{
	if(L[k]) f[i+2][k] += f[i][j] * .5;
	else
	{
		k = k + a[k];
		if(k >= n + 1) k = n + 1;
		f[i+1][k] += f[i][j] * .5;
	}
}

void solve()
{
	memset(L, 0, sizeof L);
	for(int i=1; i<=n; ++i)
	{
		scanf("%s", str);
		if(str[0] == 'L') L[i] = 1;
		else
		{
			sscanf(str, "%d", &a[i]);
		}
	}

	memset(f, 0, sizeof f);
	f[0][0] = 1.0;

	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<=n; ++j)
		{
			if(fabs(f[i][j]) < eps) continue;

			go(i, j, j+1);
			go(i, j, j+2);
		}
	}

	double ans = 0.0, half = .5000000;
	for(int i=0; i<=m; ++i) ans += f[i][n+1];

	if(ans > half + eps) printf("Bet for. ");
	else if( ans < half - eps) printf("Bet against. ");
	else printf("Push. ");
	printf("%.4lf\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		solve();
	}
}

