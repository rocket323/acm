/*
 * =======================================================
 *       Filename:  2096.cpp
 *    Description:  
 *        Created:  02/08/10 00:43:26
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 1010

double f[maxl][maxl];
bool vis[maxl][maxl];
int n, s;

double dp(int i, int j)
{
	if(vis[i][j]) return f[i][j];
	vis[i][j] = 1;

	if(i > n || j > s) return 0.0;
	if(i == n && j == s) return 0.0;

	f[i][j] = (n * s + (i-1)*j*dp(i+1, j) + i*(s-j)*dp(i, j+1) + (n-i)*(s-j)*dp(i+1, j+1)) / (n * s - i * j);
	return f[i][j];
}

int main()
{
	while(scanf("%d%d", &n, &s) != EOF)
	{
		memset(vis, 0, sizeof vis);
		printf("%.4lf\n", dp(0, 0));
	}
}

