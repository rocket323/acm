#include <stdio.h>
#include <cstring>
#define mod 11380

int f[11][11][11][31], g[11][11][11][31];
int l1, l2, l3, D;

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0][0][0] = g[0][0][0][0] = 1;

	for(int a=0; a<=l1; ++a)
	{
		for(int b=0; b<=l2; ++b)
		{
			for(int c=0; c<=l3; ++c)
			{
				if(!a && !b && !c) continue;

				g[a][b][c][0] = 0;
				for(int d=1; d<=D; ++d)
				{
					if(a) f[a][b][c][d] = f[a-1][b][c][d-1];
					if(b & !a) f[a][b][c][d] = (f[a][b][c][d] + f[a][b-1][c][d-1]) % mod;
					if(c & !a && !b) f[a][b][c][d] = (f[a][b][c][d] + f[a][b][c-1][d-1]) % mod;

					for(int x=0; x<=a; ++x)
					{
						for(int y=0; y<=b; ++y)
						{
							for(int z=0; z<=c; ++z)
							{
								if(!x && !y && !z) continue;
								if(!(a-x) && !(b-y) && !(c-z)) continue;

								f[a][b][c][d] = (f[a][b][c][d] + f[x][y][z][d] * g[a-x][b-y][c-z][d]) % mod;
								f[a][b][c][d] = (f[a][b][c][d] + g[x][y][z][d] * f[a-x][b-y][c-z][d]) % mod;
								f[a][b][c][d] = (f[a][b][c][d] - f[x][y][z][d] * f[a-x][b-y][c-z][d] % mod + mod) % mod;
							}
						}
					}

					g[a][b][c][d] = (g[a][b][c][d-1] + f[a][b][c][d]) % mod;
				}
			}
		}
	}
	printf("%d\n", f[l1][l2][l3][D]);
}

int main()
{
	scanf("%d%d%d%d", &l1, &l2, &l3, &D);
	solve();
	return 0;
}

