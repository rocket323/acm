#include <stdio.h>

int fun(int n)
{
	int ans = 0;
	while(n){ ans += n/2; n /= 2; }
	return ans;
}

int main()
{
	int n, k, a = 0;
	while(scanf("%d%d", &n, &k)!=EOF)
	{
		a = fun(n);
		a -= fun(k);
		a -= fun(n-k);
		if(a > 0) printf("0\n");
		else printf("1\n");
	}
	return 0;
}