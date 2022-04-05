#include <stdio.h>
#include <cstring>

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
	int n;	
	while(scanf("%d", &n), n)
	{
		printf("%d\n", phi(n));
	}
	return 0;
}
