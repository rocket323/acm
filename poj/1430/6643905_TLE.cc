#include <stdio.h>
#include <cstring>

int s[200][200], n = 20;

int pow(int n)
{
	return (1 << n);
}

int solve(int n, int m)
{

	//printf("%d %d\n", n, m);

	if(n == m) return 1;
	if(m == 0) return 0;
	if(m == 1 || m == 2) return 1;

	int k = 1;
	while(true)
	{
		if(pow(k) >= m && pow(k - 1) + m / 2 >= n) break;
		k++;
	}

	int flag = 0;
	if(n == 4 && m == 3) flag = 1;

	if(m > pow(k - 1)){ n -= pow(k - 1); m -= pow(k - 1); }
	else if(n - m >= pow(k - 2)) n -= pow(k - 2);
	else return 0;

	//if(flag) printf("n %d %d %d\n", n, m, k);

	return solve(n, m);
}

int main()
{
	
	/*
	memset(s, 0, sizeof s);
	s[0][0] = 1;
	for(int i=1; i<n; ++i)
	{
		s[i][1] = s[i][i] = 1;
		for(int j=2; j<i; ++j)
		{
			s[i][j] = (j * s[i-1][j] + s[i-1][j-1]) % 2;
		}
	}

	for(int i=1; i<n; ++i)
	{
		printf("%2d ", i);
		for(int j=1; j<=i; ++j)
		{
			//printf("%d ", s[i][j] % 2);
			if(s[i][j] & 1) printf("1");
			else printf("_");
		}
		puts("");
	}
	*/

	int t, n, m;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", solve(n, m));
	}

	return 0;
}

