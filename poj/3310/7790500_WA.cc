/*
 * =======================================================
 *       Filename:  3310.cpp
 *    Description:  
 *        Created:  26/10/10 00:01:14
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 500

int n, m, dd[maxl], d[maxl], ea[maxl], eb[maxl];
int a, b, flag;

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), n)
	{
		memset(d, 0, sizeof d);
		memset(dd, 0, sizeof dd);
		for(int i=0; i<m; ++i)
		{
			scanf("%d%d", &a, &b);
			ea[i] = a;
			eb[i] = b;
			d[a]++;
			d[b]++;
		}

		for(int i=0; i<m; ++i)
		{
			int a = ea[i], b = eb[i];
			if(d[a] < 2 || d[b] < 2) continue;
			dd[a]++;
			dd[b]++;
		}

		int c1 = 0, c3 = 0, c0 =0, c2 = 0;
		for(int i=1; i<=n; ++i)
		{
			if(d[i] < 2) continue;
			if(dd[i] == 1) c1++;
			else if(dd[i] > 2) c3++;
			else if(dd[i] == 2) c2++;
			else if(dd[i] == 0) c0++;
		}
		if(c1 <= 2 && c1 >= 1 && c3 == 0) flag = 1;
		else flag = 0;
		if(c0 == 1 && c1 + c2 + c3 == 0) flag = 1;
		if(!flag) printf("Graph %d is not a caterpillar.\n", ++tc);
		else printf("Graph %d is a caterpillar.\n", ++tc);
	}
	return 0;
}

