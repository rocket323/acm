#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define maxl 35
#define min(a,b) ((a<b)?a:b)

int n, d[maxl][maxl], f[maxl][maxl][maxl][maxl];

void solve()
{
	scanf("%d", &n);
	for(int i=1; i<n; ++i)
	{
		for(int j=i+1; j<=n; ++j)
		{
			scanf("%d", &d[i][j]);
			d[j][i] = d[i][j];
		}
	}

	memset(f, 0x3f, sizeof f);
	f[1][1][1][1] = 0;

	for(int i=1; i<n; ++i)
	{
		for(int a=1; a<=n; ++a)
		{
			for(int b=1; b<=n; ++b)
			{
				for(int c=1; c<=n; ++c)
				{
					if(f[i][a][b][c] == INF) continue;

					for(int s=1; s<8; ++s)
					{
						int na = a, nb = b, nc = c, sum = 0;
						if(s & 1) na = i + 1, sum += d[i+1][a];
						if(s & 2) nb = i + 1, sum += d[i+1][b];
						if(s & 4) nc = i + 1, sum += d[i+1][c];

						f[i+1][na][nb][nc] = min(f[i+1][na][nb][nc], f[i][a][b][c] + sum);
					}
				}
			}
		}
	}

	int ans = INF;
	for(int a=1; a<=n; ++a) for(int b=1; b<=n; ++b) for(int c=1; c<=n; ++c)
		ans = min(ans, f[n][a][b][c]);
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}

