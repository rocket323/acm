#include <stdio.h>
#include <cstring>
#include <algorithm>
#define INF 0x7f
using namespace std;

int g[10][10], n, m, tot, fac[20];
char f[11][11][59049];

int min(int a, int b)
{
	return (a < b) ? a : b;
}

void init()
{
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			scanf("%d", &g[i][j]);
			if(g[i][j] == 1) g[i][j] = 3;
			else if(g[i][j] == 2) g[i][j] = 1;
			else if(g[i][j] == 3) g[i][j] = 2;
		}
	}
}

int getBit(int s, int idx, int& b, int& t)
{
	for(int i=0; i<idx; ++i) s /= 3;
	t = s % 3;
	b = t * fac[idx];
}

void solve()
{
	memset(f, 0x7f, sizeof f);
	f[0][0][0] = 0;

	tot = fac[m + 1];

	for(int i=0; i<=n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			for(int k=0; k<tot; ++k)
			{
				if(f[i][j][k] == 0x7f) continue;

				int b1, b2, t1, t2;
				getBit(k, j, b1, t1);
				getBit(k, j + 1, b2, t2);

				if(g[i][j] == 3 && (b1 + b2)) continue;

				if(b1 && b2)
				{
					if(t1 != t2 || g[i][j] != 0) continue;
					f[i][j+1][k - b1 - b2] = min(f[i][j+1][k - b1 - b2], f[i][j][k] + 1);
				}
				else if(b1 + b2)
				{
					int b, t;
					if(b1){ b = b1, t = t1; } else { b = b2, t = t2; }

					if(g[i][j] == 1 || g[i][j] == 2)
					{
						if(t != g[i][j]) continue;

						f[i][j+1][k - b] = min(f[i][j+1][k - b], f[i][j][k] + 1);
					}
					else
					{
						int x = t * fac[j];
						f[i][j+1][k - b + x] = min(f[i][j+1][k - b + x], f[i][j][k] + 1);
						f[i][j+1][k - b + x * 3] = min(f[i][j+1][k - b + x * 3], f[i][j][k] + 1);
					}
				}
				else
				{
					if(g[i][j] != 1 && g[i][j] != 2)
					{
						f[i][j+1][k] = min(f[i][j+1][k], f[i][j][k]);
						
						if(g[i][j] == 3) continue;

						int t2 = 1 * fac[j], t3 = 2 * fac[j];

						f[i][j+1][k + t2 + t2 * 3] = min(f[i][j+1][k + t2 + t2 * 3], f[i][j][k] + 1);
						f[i][j+1][k + t3 + t3 * 3] = min(f[i][j+1][k + t3 + t3 * 3], f[i][j][k] + 1);
					}
					else if(g[i][j] == 1 || g[i][j] == 2)
					{
						int t = (g[i][j]) * fac[j];
						f[i][j+1][k + t] = min(f[i][j+1][k + t], f[i][j][k] + 1);
						f[i][j+1][k + t * 3] = min(f[i][j+1][k + t * 3], f[i][j][k] + 1);
					}
				}
			}
		}
		for(int k=0; k<(fac[m+1] / 3); ++k) f[i+1][0][k * 3] = f[i][m][k];
	}

	if(f[n-1][m][0] == INF) puts("0");
	else printf("%d\n", f[n-1][m][0] - 2);
}

int main()
{
	fac[0] = 1;
	for(int i=1; i<=10; ++i) fac[i] = fac[i-1] * 3;

	while(scanf("%d%d", &n, &m), (n + m))
	{
		init();
		solve();
	}
	return 0;
}

