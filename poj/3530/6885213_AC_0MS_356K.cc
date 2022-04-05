#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int m, d, l, r;

int mod(int a, int n)
{
	return (a % n + n) % n;
}

int gcd(int a, int b)
{
	if(b == 0) return a;
	else return gcd(b, a % b);
}

int solve(int m, int d, int l, int r)
{
	if(l % d == 0) return l / d;
	else if(l / d != r / d) return l / d + 1;

	int g = gcd(d, m);
	if(l % g != 0 && l / g == r / g) return -1;

	int t = solve(d, m % d, mod(-r, d), mod(-l, d));

	return ((long long)t * m + l - 1) / d + 1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &m, &d, &l, &r);

		if(l > min(r, m - 1) || d % m == 0)
		{
			puts("-1");
			continue;
		}

		d %= m;
		printf("%d\n", solve(m, d, l, r));
	}
	return 0;
}

