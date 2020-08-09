#include <stdio.h>
#include <cstring>
#include <iostream>
#define maxl 1010

using namespace std;

int n, m, x;
int f[maxl][maxl][15][2];
char s[maxl], t[maxl];

void update(int &a, int v)
{
	if (a < v) a = v;
}

int main()
{
	while (scanf("%d%d%d", &n, &m, &x) != EOF)
	{
		scanf("%s", s + 1);
		scanf("%s", t + 1);

		int ans = 0;
		memset(f, 0x80, sizeof f);
		f[0][0][0][0] = 0;
		for (int i = 0; i <= n; ++i)
		{
			for (int j = 0; j <= m; ++j)
			{
				for (int k = 0; k <= x; ++k)
				{
					if (f[i][j][k][0] >= 0)
					{
						// printf("i[%d], j[%d], k[%d], 0: %d\n", i, j, k, f[i][j][k][0]);
						update(f[i+1][j][k][0], f[i][j][k][0]);
						update(f[i][j+1][k][0], f[i][j][k][0]);

						if (s[i + 1] == t[j + 1])
						{
							update(f[i+1][j+1][k+1][1], f[i][j][k][0] + 1);
						}
					}

					if (f[i][j][k][1] >= 0)
					{
						// printf("i[%d], j[%d], k[%d], 1: %d\n", i, j, k, f[i][j][k][1]);
						update(f[i+1][j][k][0], f[i][j][k][1]);
						update(f[i][j+1][k][0], f[i][j][k][1]);

						if (s[i + 1] == t[j + 1])
						{
							update(f[i+1][j+1][k][1], f[i][j][k][1] + 1);
							update(f[i+1][j+1][k+1][1], f[i][j][k][1] + 1);
						}
					}
				}
			}
		}

		ans = max(f[n][m][x][0], f[n][m][x][1]);
		printf("%d\n", ans);
	}

	return 0;
}

