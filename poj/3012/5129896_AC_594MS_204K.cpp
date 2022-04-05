#include <stdio.h>
#define ll long long

int n, m,k;

int pow(int a, int n, int mod)
{
	if(n==0) return 1;
	int mid = pow(a, n/2, mod);
	mid = ((ll)mid * mid)%mod;
	if(n&1) mid = ((ll)mid * a)%mod;
	return mid;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &k, &m);
		int a = pow(10, k, m) + 1;
		a = pow(a, n, m);
		printf("%d\n", a);
	}
	return 0;
}
