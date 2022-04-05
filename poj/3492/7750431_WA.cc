/*
 * =======================================================
 *       Filename:  3492.cpp
 *    Description:  
 *        Created:  16/10/10 09:52:02
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 2000010

bool f[maxl];
int n, a[maxl], sum, mx;

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		int g = -1;
		mx = 0;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &a[i]);
			if(g == -1) g = a[i];
			else g = __gcd(g, a[i]);
			if(a[i] > mx) mx = a[i];
		}

		if(g != 1)
		{
			puts("INF");
			continue;
		}

		memset(f, 0, sizeof f);
		f[0] = 1;
		int sum = mx * 30;
		for(int i=1; i<=n; ++i)
			for(int j=a[i]; j<=sum; ++j)
				f[j] |= f[j-a[i]];
		for(int j=sum; j>=0; --j)
		{
			if(f[j]) continue;
			printf("%d\n", j);
			break;
		}
	}
	return 0;
}

