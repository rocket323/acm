/*
 * =======================================================
 *       Filename:  3311.cpp
 *    Description:  
 *        Created:  26/10/10 10:46:23
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <algorithm>
using namespace std;
#include <cstring>

int g[20][20], n, a[20];

int main()
{
	while(scanf("%d", &n), n)
	{
		for(int i=0; i<=n; ++i)
			for(int j=0; j<=n; ++j)
				scanf("%d", &g[i][j]);
		for(int k=0; k<=n; ++k)
			for(int i=0; i<=n; ++i)
				for(int j=0; j<=n; ++j)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		for(int i=0; i<n; ++i) a[i] = i + 1;

		int ans = 0x3f3f3f3f;
		while(next_permutation(a, a + n))
		{
			int tmp = g[0][a[0]];
			for(int i=1; i<n; ++i) tmp += g[a[i-1]][a[i]];
			tmp += g[a[n-1]][0];
			if(tmp < ans) ans = tmp;
		}
		printf("%d\n", ans);
	}
	return 0;
}

