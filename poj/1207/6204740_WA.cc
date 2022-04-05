#include <stdio.h>
#include <cstring>

int c[10010], a, b;

int fun(int n)
{
	int cnt = 0;
	while(n != 1)
	{
		cnt++;
		if(n & 1) n = 3 * n + 1;
		else n /= 2;
	}
	return cnt;
}

int solve(int a, int b)
{
	int max = 0;
	for(int i=a; i<=b; ++i) if(c[i] > max) max = c[i];
	return max;
}

int main()
{
	for(int i=1; i<10000; ++i)
	{
		c[i] = fun(i) + 1;
	}

	while(scanf("%d%d", &a, &b) != EOF)
	{
		printf("%d %d %d\n", a, b, solve(a, b));
	}
	return 0;
}
