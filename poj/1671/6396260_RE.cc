#include <stdio.h>
#include <cstring>

double s[100][100];
int n;

int main()
{

	s[0][0] = 1;

	for(int i=1; i<=100; ++i)
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

