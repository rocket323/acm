#include <stdio.h>
#include <cstring>
#define maxl 2010

int f[12][maxl], n, m;

int main()
{
	int t, tc = 0;
	scanf("%d", &t);
	memset(f, 0, sizeof f);
	for(int i=1; i<maxl; ++i) f[1][i] = 1;

	for(int i=2; i<=10; ++i)
	{
		for(int j=1; j<maxl; ++j)
		{
			for(int k=1; k<=j/2; ++k)
			{
				f[i][j] += f[i-1][k];
			}
		}
	}
	while(t--)
	{
		scanf("%d%d", &n, &m);
		int ans = 0;
		for(int i=1; i<=m; ++i) ans += f[n][i];
		printf("Case %d: n = %d, m = %d, # lists = %d\n", ++tc, n, m, ans);
	}
}

