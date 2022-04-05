/*
 * =======================================================
 *       Filename:  3172.cpp
 *    Description:  
 *        Created:  19/10/10 12:07:51
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int x, c, n, a[2000];

int main()
{
	while(scanf("%d%d", &n, &c) != EOF)
	{
		for(int i=0; i<n; ++i) scanf("%d", &a[i]);
		sort(a, a + n);
		x = c;
		for(int i=n-1; i>=0; --i)
		{
			if(c >= a[i]) c -= a[i];
		}
		printf("%d\n", x - c);
	}
	return 0;
}

