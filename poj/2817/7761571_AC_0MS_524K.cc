/*
 * =======================================================
 *       Filename:  2817.cpp
 *    Description:  
 *        Created:  19/10/10 10:34:34
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define contain(a,b) ((a & (1 << b)) ? 1 : 0)

int g[12][12], f[3000][12], n;
char s[23][23];

int calc(char s1[], char s2[])
{
	int ans = 0;
	for(int i=0; s1[i] && s2[i]; ++i)
	{
		if(s1[i] == s2[i]) ans++;
	}
	return ans;
}

void init()
{
	for(int i=0; i<n; ++i) scanf("%s", s[i]);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(i == j) continue;
			g[i][j] = 0;
			for(int k=0; s[j][k]; ++k) g[i][j] = max(g[i][j], calc(s[i], s[j] + k));
			for(int k=0; s[i][k]; ++k) g[i][j] = max(g[i][j], calc(s[i] + k, s[j]));
		}
	}
}

void solve()
{
	memset(f, 0x80, sizeof f);
	for(int i=0; i<n; ++i) f[1<<i][i] = 0;

	for(int x=1; x<(1<<n); ++x)
	{
		for(int i=0; i<n; ++i)
		{
			if(!contain(x, i)) continue;
			for(int j=0; j<n; ++j)
			{
				if(contain(x, j)) continue;
				int tmp = x | (1 << j);
				f[tmp][j] = max(f[tmp][j], f[x][i] + g[i][j]);
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; ++i) ans = max(ans, f[(1<<n)-1][i]);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n), n > 0)
	{
		init();
		solve();
	}
	return 0;
}

