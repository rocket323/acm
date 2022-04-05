#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define maxl 1000010

int list[maxl], top;
bool check[maxl], f[maxl];

void preInit()
{
	memset(f, 0, sizeof f);

	top = 0;	
	for(int i=2; (long long)i<=0x7fffffff/i; ++i)
	{
		if(f[i] == 1) continue;
		list[top++] = i;
		for(int j=i*i; j<maxl; j+=i) f[j] = 1;
	}
}

int pow(int a, int x, int n)
{
	if(x == 0) return 1;
	int mid = pow(a, x / 2, n);
	if(mid == 0) return 0;

	int y = (long long)mid * mid % n;
	if(y == 1 && mid != 1 && mid != n - 1) return 0;

	if(x & 1) y = (long long)y * a % n;
	return y;
}

bool isPrime(int n)
{
	if(n == 1) return 0;
	if(n == 2) return 1;

	for(int i=0; i<2; ++i)
	{
		int a = rand() % (n - 2) + 2;
		if(pow(a, n - 1, n) != 1) return 0;
	}
	return 1;
}

int main()
{
	int l, u;
	
	preInit();
	
	while(scanf("%d%d", &l, &u) != EOF)
	{
		int a = -1, b = -1, c = -1, d = -1, lst = -1;
		
		memset(check, 0, sizeof check);
		if(l == 1) l = 2;
		for(int i=0; i<top && (long long)list[i]*list[i]<=u; ++i)
		{
			int x = l / list[i] + (l % list[i] > 0);
			if(x == 1) x = 2;
			if((long long)list[i] * x > 0x7fffffff) continue;
			for(long long j=list[i]*x; j<=u; j+=list[i])
			{
				check[j - l] = 1;
			}
		}
		
		for(long long i=l; i<=u; ++i)
		{
			if(check[i - l]) continue;
			if(lst == -1) lst = i;
			else
			{
				if(a == -1) a = lst, b = i;
				else if(i - lst < b - a) a = lst, b = i;

				if(c == -1) c = lst, d = i;
				else if(i - lst > d - c) c = lst, d = i;

				lst = i;
			}
		}

		if(a == -1) puts("There are no adjacent primes.");
		else printf("%d,%d are closest, %d,%d are most distant.\n", a, b, c, d);
	}
}
