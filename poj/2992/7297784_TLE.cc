#include <stdio.h>
#include <cstring>
#define maxl 1000

int f[maxl + 10], n, m;
int list[1000], top;
long long c[1000];

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

void calc(int n, int sgn)
{
	for(int i=0; i<top && list[i]<=n; ++i)
	{
		int num = n;
		long long cnt = 0;
		while(num)
		{
			cnt += num / list[i];
			num /= list[i];
		}
		c[i] += (long long)sgn * cnt;
	}
}

int main()
{
	init();

	while(scanf("%d%d", &n, &m) != EOF)
	{
		memset(c, 0, sizeof c);
		calc(n, 1);
		calc(n - m, -1);
		calc(m, -1);

		long long ans = 1;
		for(int i=0; i<top; ++i) ans *= (long long)(c[i] + 1);
		printf("%lld\n", ans);
	}

	return 0;
}

