/*
 * =======================================================
 *       Filename:  2825new.cpp
 *    Description:  
 *        Created:  19/10/10 10:17:02
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>

int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
	{
		if(n % 4 == 2 || n % 4 == 3)
		{
			puts("0");
			continue;
		}
		int now = n, num;
		for(int i=1; i<=n; ++i)
		{
			if(i == n / 4 * 3) num = n / 4 * 3 + n % 4;
			else if(i == n) num = n / 2 + n % 4;
			else
			{
				while(now == n / 4 * 3 + n % 4 || now == n / 2 + n % 4) now--;
				num = now--;
			}
			printf("%d%c", num, (i == n) ? '\n' : ' ');
		}
	}
	return 0;
}

