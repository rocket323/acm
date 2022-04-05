#include <stdio.h>
#include <cstring>

int gcd(int a, int b)
{
	if(!b) return a;
	else return gcd(b, a % b);
}

int main()
{
	int n, tc = 0;
	while(scanf("%d", &n) != EOF)
	{
		int ans = 0;
		for(int i=0; i<=n; ++i) for(int j=0; j<=n; ++j) ans += (gcd(i, j) == 1);
		printf("%d %d %d", ++tc, n, ans);
	}
	return 0;
}
