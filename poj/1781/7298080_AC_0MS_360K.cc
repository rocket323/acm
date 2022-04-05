#include <stdio.h>
#include <cstring>

int f[10];
char str[5];

int calc(char str[])
{
	return ((str[0] - '0') * 10 + (str[1] - '0')) * (f[str[3] - '0']);
}

int main()
{
	f[0] = 1;
	for(int i=1; i<10; ++i) f[i] = f[i-1] * 10;
	while(scanf("%s", str), strcmp(str, "00e0"))
	{
		int n = calc(str);

		int x = 1;
		while(x <= n) x <<= 1;
		x >>= 1;
		x = n - x;
		printf("%d\n", 2 * x + 1);
	}
	return 0;
}

