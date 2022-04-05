/*
 * =======================================================
 *       Filename:  3607.cpp
 *    Description:  组合计数
 *        Created:  07/08/10 16:09:33
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
#define mod 9973
#define maxl 1010
using namespace std;

int n, c[maxl][maxl], f[maxl][maxl], K, m;

int main()
{
	memset(c, 0, sizeof c);
	for(int i=0; i<maxl; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j=1; j<i; ++j)
		{
			c[i][j] = c[i-1][j-1] + c[i-1][j];
			if(c[i][j] >= mod) c[i][j] -= mod;
		}
	}

	int t, n, m, k;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &K);
		for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j) f[i][j] = 0;
		f[0][0] = 1;

		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=i; ++j)
			{
				f[i][j] = (f[i-1][j] * j + c[i-1][K-1] * f[i-K][j-1]) % mod;
			}
		}
		int sum = 0;
		for(int i=1; i<=n; ++i) sum = (sum + f[n][i]) % mod;

		if(K == 0) printf("%d\n", sum);
		else printf("%d\n", f[n][m]);
	}

	return 0;
}

