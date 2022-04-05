#include <stdio.h>
#include <cstring>

int f[1010][1010];

int gcd(int a, int b)
{
	if(!b) return a;
	else return gcd(b, a % b);
}

int main()
{
	int n, tc = 0;
	for(int i=0; i<=1000; ++i) for(int j=0; j<=1000; ++j) f[i][j] = gcd(i, j);
	while(scanf("%d", &n) != EOF)
	{
		int ans = 0;
		for(int i=0; i<=n; ++i) for(int j=0; j<=n; ++j) ans += (f[i][j] == 1);
		printf("%d %d %d\n", ++tc, n, ans);
	}
	return 0;
}
