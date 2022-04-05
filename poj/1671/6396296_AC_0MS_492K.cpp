#include <stdio.h>
#include <cstring>
#define maxl 200

double s[maxl][maxl];
int n;

int main()
{

	s[0][0] = 1;

	for(int i=1; i<maxl; ++i)
	{
		s[i][1] = s[i][i] = 1;
		for(int j=2; j<i; ++j) s[i][j] = j * s[i-1][j] + s[i-1][j-1];
	}

	while(scanf("%d", &n), n)
	{
		double ans = 0;
		for(int i=1; i<=n; ++i) ans += s[n][i];
		printf("%d %.0lf\n", n, ans);
	}
	return 0;
}

