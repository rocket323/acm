#include <stdio.h>
#include <cstring>

int n;

int phi(int n)
{
	int ans = n;
	for(int i=2; i<=n/i; ++i)
	{
		if(n % i == 0) ans = ans / i * (i - 1);
		while(n % i == 0) n /= i;
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		long long ans = 0;
		for(int i=1; i<=n/i; ++i)
		{
			ans += (long long)i * phi(n / i);
			if(i * i != n) ans += (long long)(n / i) * phi(i);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}

