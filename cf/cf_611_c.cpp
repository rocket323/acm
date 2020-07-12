#include <stdio.h>
#include <cstring>
#define maxl 502

int n, m, q, a, b, c, d;
char s[maxl][maxl];
int sr[maxl][maxl], sc[maxl][maxl];

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=0; i<n; ++i) scanf("%s", s[i]);

	memset(sr, 0, sizeof sr);
	memset(sc, 0, sizeof sc);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			if(j == 1) { sr[i][j] = 0; continue; }
			char c2 = s[i-1][j-2], c1 = s[i-1][j-1];
			sr[i][j] = sr[i][j-1];
			if(c2 == '.' && c1 == '.')
			{
				sr[i][j] = sr[i][j-1] + 1;
			}
		}
	}

	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			if(j == 1) { sc[i][j] = 0; continue; }
			char c2 = s[j-2][i-1], c1 = s[j-1][i-1];
			sc[i][j] = sc[i][j-1];
			if(c2 == '.' && c1 == '.')
			{
				sc[i][j] = sc[i][j-1] + 1;
			}
		}
	}

	scanf("%d", &q);
	for(int i=0; i<q; ++i)
	{
		int r1, c1, r2, c2;
		scanf("%d%d%d%d", &r1, &c1, &r2, &c2);

		/*
		for(int x=r1; x<=r2; ++x)
		{
			for(int y=c1; y<=c2; ++y)
			{
				printf("%c", s[x-1][y-1]);
			}
			puts("");
		}
		*/

		int ans = 0;
		for(int x=r1; x<=r2; ++x)
		{
			if(s[x-1][c1-1] == '#') ans += sr[x][c2] - sr[x][c1-1];
			else ans += sr[x][c2] - sr[x][c1];
		}
		for(int x=c1; x<=c2; ++x)
		{
			if(s[r1-1][x-1] == '#') ans += sc[x][r2] - sc[x][r1-1];
			else ans += sc[x][r2] - sc[x][r1];
		}
		printf("%d\n", ans);
	}

	return 0;
}

