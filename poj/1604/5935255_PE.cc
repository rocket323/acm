#include <stdio.h>
#include <cstring>

int a[5] = {1, 1, 2, 1, 4};
int b[4] = {1, 2, 4, 3};

int solve(int n)
{
	int c = 0, ans = 1, nn = n;
	while(n)
	{
		c += n / 5;
		ans = (ans * a[n % 5]) % 5;
		n /= 5;
	}
	ans = (ans * b[c % 4]) % 5;
	if((ans & 1) && nn > 1) ans += 5;
	return ans;
}

int main()
{
	int n;
	while(scanf("%d", &n) != EOF) printf("%d -> %d\n", n, solve(n));
	return 0;
}

