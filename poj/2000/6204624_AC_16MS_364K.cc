#include <stdio.h>
#include <cstring>
#define ll long long

int fun(int n)
{
	return (n + 1) * (2 * n + 1) * n / 6;
}

int bin(int n)
{
	int l = 0, r = 10000, ans, mid;
	while(l <= r)
	{
		mid = (l + r) / 2;
		if((mid + 1) * mid / 2 < n)
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return ans;
}

int solve(int n)
{
	int k = bin(n);

	n -= (k + 1) * k / 2;

	return (k + 1) * n + fun(k);
}

int main()
{
	int n;
	while(scanf("%d", &n), n)
	{
		printf("%d %d\n", n, solve(n));
	}
	return 0;
}
