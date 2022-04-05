#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

int n, E, D, f[21][101][101];

void solve()
{
	memset(f, 0x3f, sizeof f);
	for(int i=0; i<=E; ++i) f[1][i][0] = 0;

	for(int e=0; e<=E; ++e)
	{
		for(int d=0; d<=D; ++d)
		{
			for(int j=0; j*j<=e && j<=d; ++j) f[1][e][d] = min(f[1][e][d], f[1][e-j*j][d-j] + 1);
		}
	}

	for(int i=2; i<=n; ++i)
	{
		for(int e=0; e<=E; ++e)
		{
			for(int d=0; d<=D; ++d)
			{
				for(int j=0; j<=e && j<=d; ++j) f[i][e][d] = min(f[i][e][d], f[i-1][e-j][d-j] + f[1][e][j]);
			}
		}
	}

	printf("%d\n", f[n][E][D]);
}

int main()
{
	while(scanf("%d%d%d", &n, &E, &D)!=EOF) solve();
	return 0;
}
