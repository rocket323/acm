#include <stdio.h>
#include <cstring>

long long n;

bool sg(long long n)
{
	long long num = 1, cnt = 0;

	if(n <= 9) return 1;
	else if(n < 18) return 0;

	while(num * 18 < n) num *= 18;

	//printf("%lld %lld\n", n, num);

	return (num * 9 >= n);
}

int main()
{
	long long n;
	while(scanf("%I64d", &n) != EOF)
	{
		long long k = sg(n);
		if(k) puts("Stan wins.");
		else puts("Ollie wins.");
	}
	return 0;
}

