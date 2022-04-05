#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#define ADD 10000

int n, a[110], f[110][2 * ADD + 10];
int op[2 * ADD + 10], t, sum, p[110][2 * ADD + 10];

void init()
{
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
}

void solve()
{
	if(n == 1)
	{
		
		return;
	}
	if(n == 2)
	{
while(1);
		puts("1");
		return;
	}

	memset(f, 0, sizeof f);
	f[2][a[1] - a[2] + ADD] = 1;
	p[2][a[1] - a[2] + ADD] = a[1];
	p[1][a[1] + ADD] = 0;

	sum = abs(a[1]) + abs(a[2]);
	for(int i=2; i<n; ++i)
	{
		for(int j=-sum; j<=sum; ++j)
		{
			if(f[i][j + ADD])
			{
				f[i+1][j - a[i+1] + ADD] = 1;
				p[i+1][j - a[i+1] + ADD] = j;

				f[i+1][j + a[i+1] + ADD] = 1;
				p[i+1][j + a[i+1] + ADD] = j;
			}
		}
		sum += abs(a[i]);
	}

	//printf("n %d\n", f[n][t + ADD]);

	memset(op, -1, sizeof op);
	int k = t, i = n;
	while(k != 0)
	{
		//printf("h %d\n", k);
		if(k - p[i][k + ADD] == a[i]) op[i] = 1;
		else op[i] = 0;
		k = p[i][k + ADD];
		i--;
	}

	//for(int i=1; i<=n; ++i) printf("%d ", op[i]);
	//puts("");

	for(int i=3; i<=n; ++i)
	{
		if(op[i] == 1) puts("2");
		else puts("1");
	}
	puts("1");

}

int main()
{
	while(scanf("%d%d", &n, &t) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

