#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

int a[200], f[200][200], n;

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);

	memset(f, 0x3f, sizeof f);
	for(int i=1; i<=n; ++i)
	{
		f[i][i] = 0;
		if(i < n) f[i][i+1] = 0;
	}

	for(int k=3; k<=n; ++k)
	{
		for(int i=1, j=i+k-1; j<=n; ++i, ++j)
		{
			for(int x=i+1; x<j; ++x)
			{
				f[i][j] = min(f[i][j], f[i][x] + f[x][j] + a[i] * a[x] * a[j]);
			}
		}
	}

	printf("%d\n", f[1][n]);

	return 0;
}

