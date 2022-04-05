/*
 * =======================================================
 *       Filename:  3146new.cpp
 *    Description:  lucas's theorem
 *        Created:  17/08/10 00:11:47
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define mod 10000

int pow[10000], list[1000], p, n, top;

int solve(int now)
{
	int ans = 1;
	for(int i=0; i<top; ++i) ans = (ans * (list[i] + 1)) % mod;
	return ans;
}

int main()
{
	int tc = 0;

	while(scanf("%d%d", &p, &n), p)
	{

		pow[0] = 1;
		for(int i=1; i<=100; ++i) pow[i] = (pow[i-1] * p) % mod;

		top = 0;
		int num = n;
		while(num)
		{
			list[top++] = num % p;
			num /= p;
		}

		int ans = solve(top - 1);
		printf("Case %d: %04d\n", ++tc, ans);
	}
	return 0;
}

