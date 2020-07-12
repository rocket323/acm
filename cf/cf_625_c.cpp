#include <stdio.h>
#include <cstring>
#define maxl 516

int n, k;
int a[maxl][maxl], x;

void Process(int r1, int r2)
{
	for(int i = 1; i <= n; ++i)
	{
		for(int j = r2; j >= r1; --j)
		{
			a[i][j] = x--;
		}
	}
}

int main()
{
	while(scanf("%d%d", &n, &k) != EOF)
	{
		x = n * n;
		Process(k, n);
		Process(1, k - 1);
		int ans = 0;
		for(int i = 1; i <= n; ++i) ans += a[i][k];
		printf("%d\n", ans);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				printf("%d%c", a[i][j], (j == n) ? '\n' : ' ');
	}

	return 0;
}

