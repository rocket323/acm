#include <stdio.h>
#include <cstring>
#define maxl 600

int a[maxl][maxl], n, k;

void dfs(int k)
{
	if(k == 0)
	{
		a[1][1] = 1;
		return;
	}
	dfs(k - 1);
	int x = 1 << (k - 1);
	for(int i=1; i<=x; ++i) for(int j=1; j<=x; ++j) a[i + x][j + x] = a[i][j];

	for(int i=1; i<=x; ++i)
	{
		for(int j=1; j<=x; ++j)
		{
			int num = (i + j - 2) % x;
			a[i + x][j] = 2 * x + num;
			a[i][j + x] = 3 * x + num;
		}
	}
}

int main()
{
	while(scanf("%d", &k) != EOF)
	{
		dfs(k);
		n = 1 << k;
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=n; ++j)
			{
				printf("%d%c", a[i][j], (j == n) ? '\n': ' ');
			}
		}
	}
	return 0;
}
