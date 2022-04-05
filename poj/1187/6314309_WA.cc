#include <stdio.h>
#include <cstring>
#define mod 11380

short f[11][11][11][31], g[11][11][11][31];
int l1, l2, l3, D;

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0][0][0] = g[0][0][0][0] = 1;
	for(int i=1; i<=D; ++i) g[0][0][0][i] = 1;

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

					for(int x=0; x<=a; ++x)
					{
						for(int y=0; y<=b; ++y)
						{
							for(int z=0; z<=c; ++z)
							{
								// { }
								if(x)
								{
									f[a][b][c][d] = (f[a][b][c][d] + f[x-1][y][z][d-1] * (int)g[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] + g[x-1][y][z][d-1] * (int)f[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] - f[x-1][y][z][d-1] * (int)f[a-x][b-y][c-z][d] % mod + mod) % mod;
								}

								// [ ]
								if(y && !x)
								{
									f[a][b][c][d] = (f[a][b][c][d] + f[x][y-1][z][d-1] * (int)g[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] + g[x][y-1][z][d-1] * (int)f[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] - f[x][y-1][z][d-1] * (int)f[a-x][b-y][c-z][d] % mod + mod) % mod;
								}
								
								// ( )
								if(z && !x && !y)
								{
									f[a][b][c][d] = (f[a][b][c][d] + f[x][y][z-1][d-1] * (int)g[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] + g[x][y][z-1][d-1] * (int)f[a-x][b-y][c-z][d]);
									f[a][b][c][d] = (f[a][b][c][d] - f[x][y][z-1][d-1] * (int)f[a-x][b-y][c-z][d] % mod + mod) % mod;
								}
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

