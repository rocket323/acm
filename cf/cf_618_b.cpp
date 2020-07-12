#include <stdio.h>
#include <cstring>
#define maxl 100
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, ri, rj;
int a[maxl][maxl], b[maxl];

bool Check(int x)
{
	b[x] = n;
	for(int i = 1; i <= n; ++i) if(x != i) b[i] = a[x][i];

	// check
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(i == j) continue;
			if(min(b[i], b[j]) != a[i][j]) return false;
		}
	}
	for(int i = 1; i <= n; ++i) printf("%d%c", b[i], (i == n) ? '\n' : ' ');
	return true;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n; ++j)
			{
				scanf("%d", &a[i][j]);
				if(a[i][j] == n - 1)
				{
					ri = i;
					rj = j;
				}
			}
		}
		if(Check(ri)) continue;
		if(Check(rj)) continue;
	}
	return 0;
}

