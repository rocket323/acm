#include <stdio.h>
#include <cstring>

int f[1010][1010], cnt[1010][1010];

int gcd(int a, int b)
{
	if(!b) return a;
	else return gcd(b, a % b);
}

int main()
{
	int n, tc = 0;
	for(int i=0; i<=1000; ++i)
	{
		cnt[i][0] = (i == 1);
		for(int j=1; j<=1000; ++j)
		{
			f[i][j] = gcd(i, j);
			if(f[i][j] == 1) cnt[i][j] = cnt[i][j-1] + 1;
			else cnt[i][j] = cnt[i][j-1];
		}
	}
	while(scanf("%d", &n) != EOF)
	{
		int ans = 0;
		for(int i=0; i<=n; ++i) ans += cnt[i][n];
		printf("%d %d %d\n", ++tc, n, ans);
	}
	return 0;
}
