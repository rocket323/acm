#include <stdio.h>
#include <cstring>

int c, n;

int phi(int n)
{
	int ans = n;
	for(int i=2; i*i<=n; ++i)
	{
		if(n % i == 0)
		{
			ans = ans / i * (i - 1);
			while(n % i == 0) n /= i;
		}
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}

int pow(int a, int n)
{
	int ans = 1;
	for(int i=1; i<=n; ++i) ans *= a;
	return ans;
}

int main()
{
	while(scanf("%d%d", &c, &n), (c + n))
	{
		int ans = 0;
		for(int i=1; i<=n; ++i)
		{
			if(n % i) continue;
			ans += phi(i) * pow(c, n / i);
		}
		if(n & 1) ans += n * pow(c, (n + 1) / 2);
		else ans += (pow(c, n / 2) + pow(c, (n + 2) / 2)) * n / 2;

		ans /= 2 * n;

		printf("%d\n", ans);
	}
	return 0;
}

