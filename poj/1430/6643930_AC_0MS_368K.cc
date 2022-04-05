#include <stdio.h>
#include <cstring>
#define pow(x) (1LL<<(x))

int solve(int n, int m)
{
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

	return solve(n, m);
}

int main()
{
	int t, n, m;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", solve(n, m));
	}

	return 0;
}

