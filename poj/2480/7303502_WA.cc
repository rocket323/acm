#include <stdio.h>
#include <cstring>

int n;

int phi(int p, int k)
{
	if(k == 0) return 1;
	int ans = 1;
	for(int i=1; i<k; ++i) ans *= p;
	ans *= (p - 1);
	return ans;
}

long long calc(int p, int k)
{
	int ans = 0, num = 1;
	for(int i=0; i<=k; ++i, num*=p)
	{
		ans += num * phi(p, k - i);
	}
	return ans;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		long long ans = 1;
		for(int i=2; i<=n/i; ++i)
		{
			if(n % i) continue;
			int cnt = 0;
			while(n % i == 0)
			{
				cnt++;
				n /= i;
			}
			long long k = calc(i, cnt);
			ans *= k;
		}
		if(n > 1) ans *= calc(n, 1);
		printf("%I64d\n", ans);
	}
	return 0;
}

