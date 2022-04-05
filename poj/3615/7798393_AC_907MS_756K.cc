/*
 * =======================================================
 *       Filename:  3615.cpp
 *    Description:  
 *        Created:  27/10/10 22:56:13
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define maxl 305

int n, m, t;
int g[maxl][maxl];

int main()
{
	while(scanf("%d%d%d", &n, &m, &t) != EOF)
	{
		memset(g, 0x3f, sizeof g);
		int a, b, c;
		for(int i=0; i<m; ++i)
		{
			scanf("%d%d%d", &a, &b, &c);
			g[a][b] = min(g[a][b], c);
		}
		for(int k=1; k<=n; ++k)
			for(int i=1; i<=n; ++i)
				for(int j=1; j<=n; ++j)
					g[i][j] = min(g[i][j], max(g[i][k], g[k][j]));
		for(int i=0; i<t; ++i)
		{
			scanf("%d%d", &a, &b);
			if(g[a][b] == INF) puts("-1");
			else printf("%d\n", g[a][b]);
		}
	}
	return 0;
}

