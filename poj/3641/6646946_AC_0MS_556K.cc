#include <stdio.h>
#include <cstring>
#include <stdlib.h>

int a, p;

int pow2(int a, int x, int n)
{
	if(x == 0) return 1;
	int mid = pow2(a, x / 2, n);
	if(mid == 0) return 0;

	int y = ((long long)mid * mid) % n;
	if(y == 1 && mid != 1 && mid != n - 1) return 0;

	if(x & 1) y = ((long long)y * a) % n;
	return y;
}

bool isPrime(int n)
{
	if(n == 1) return 0;
	if(n == 2) return 1;

	for(int i=0; i<5; ++i)
	{
		int a = rand() % (n - 2) + 2;
		if(pow2(a, n - 1, n) != 1) return 0;
	}
	return 1;
}

int pow(int a, int n, int mod)
{
	int ans = 1, t = a % mod;
	while(n)
	{
		if(n & 1) ans = ((long long)ans * t) % mod;
		t = ((long long)t * t) % mod;
		n >>= 1;
	}
	return ans;
}

int main()
{
	while(scanf("%d%d", &p, &a), (a + p))
	{
		if(!isPrime(p) && pow(a, p, p) == a) puts("yes");
		else puts("no");
	}
	return 0;
}

