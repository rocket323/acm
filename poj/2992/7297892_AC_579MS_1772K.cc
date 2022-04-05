#include <stdio.h>
#include <cstring>
#define maxl 1000

int f[maxl + 10], n, m;
int list[1000], top;
int c[600][600];

void init()
{
	top = 0;
	memset(f, 0, sizeof f);
	for(int i=2; i<=maxl/i; ++i)
	{
		if(f[i] == 1) continue;
		for(int j=i*i; j<maxl; j+=i) f[j] = 1;
	}
	for(int i=2; i<maxl; ++i) if(!f[i]) list[top++] = i;
}

void calc(int n)
{
	for(int i=0; i<top && list[i]<=n; ++i)
	{
		int num = n;
		int cnt = 0;
		while(num)
		{
			cnt += num / list[i];
			num /= list[i];
		}
		c[n][i] += cnt;
	}
}

int main()
{
	init();

	memset(c, 0, sizeof c);
	for(int i=1; i<500; ++i) calc(i);

	while(scanf("%d%d", &n, &m) != EOF)
	{
		long long ans = 1;

		for(int i=0; i<top && list[i]<=n; ++i)
		{
			int tmp = c[n][i];
			tmp -= c[m][i];
			tmp -= c[n - m][i];
			ans *= (long long)(tmp + 1);
		}

		printf("%I64d\n", ans);
	}

	return 0;
}

