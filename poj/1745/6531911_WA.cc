#include <stdio.h>
#include <cstring>

int f[2][200], n, k, num[20000];

void init()
{
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; ++i) scanf("%d", &num[i]);
}

int mod(int a, int m)
{
	return (a % m + m) % m;
}

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1;

	int idx = 0;
	for(int i=0; i<n; ++i)
	{
		memset(f[idx^1], 0, sizeof f[idx^1]);

		for(int j=0; j<k; ++j)
		{
			if(!f[idx][j]) continue;

			f[idx^1][mod(j + num[i+1], k)] = 1;
			if(i > 1) f[idx^1][mod(j - num[i+1], k)] = 1;
		}
		idx ^= 1;
	}

	if(f[idx][0]) puts("Divisible");
	else puts("Not divisible");
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

