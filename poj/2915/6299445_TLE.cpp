#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define MaxL 201
#define INF (n * m)
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

short n, m, f[MaxL][MaxL][22], pre[MaxL], low[MaxL][MaxL][22], g[22][22];
short cnt[MaxL], suf[MaxL];
unsigned char r[22][22][MaxL][MaxL], s[22][22][MaxL][MaxL];
char T[MaxL], S[MaxL];

void init()
{
    scanf("%s", T);
    n = 0;
    for(short i=0; T[i]; ++i)
    {
        n++;
        cnt[n] = 1;
        S[n] = T[i];
        while(T[i+1] && T[i+1] == T[i]){ i++; cnt[n]++; }
    }

    memset(pre, -1, sizeof pre);
    for(short i=2; i<=n; ++i)
    {
        for(short j=i-1; j>=1; --j)
        {
            if(S[j] == S[i]){ pre[i] = j; break; }
        }
    }
}

void solve()
{
	//clock_t x = clock();
	memset(r, 0xff, sizeof r);
	memset(s, 0xff, sizeof s);
    for(short i=1; i<=n; ++i)
	{
		low[i][i][m] = INF;
        if(cnt[i] >= m) f[i][i][m] = 0;
        else f[i][i][m] = INF;

		for(short k=m-1; k>=1; --k)
		{
			if(k >= cnt[i]) f[i][i][k] = k - cnt[i];
            else f[i][i][k] = INF;
			low[i][i][k] = min(f[i][i][k], low[i][i][k+1]);
		}

		f[i][i][0] = go(cnt[i]);
        low[i][i][0] = f[i][i][0];

		for(short a=0; a<=m; ++a)
			for(short b=0; b<=m; ++b)
			{
				r[a][b][i][i] = i;
				s[a][b][i][i] = i;
			}
	}
	//clock_t y = clock();
	//printf("%d ms\n", y - x);

	int sum1 = 0, sum2 = 0, sum3 = 0;
    short tmp;
    for(short l=2; l<=n; ++l)
    {
        for(short i=1, j=i+l-1; j<=n; ++i, ++j)
        {

			//clock_t t1 = clock();

			for(int k=1; k<m; ++k)
			{
                f[i][j][k] = f[i][j-1][0] + f[j][j][k];
				r[k][0][i][j] = j - 1;
			}

			if(pre[j] != -1)
			{
				for(short k=1; k<m; ++k)
				{
					for(short c=0; c<=k; ++c)
					{
						short e = max(i, r[k][c][i][pre[j]]);
						for(short p=min(pre[j], r[k][c][i+1][j]); p >= e; p=pre[p])
						{
							if((tmp = f[i][p][c] + f[p+1][j][k-c]) < f[i][j][k])
							{
								f[i][j][k] = tmp;
								r[k][c][i][j] = p;
							}
						}
					}
				}
			}
			//clock_t t2 = clock();
			//sum1 += (t2 - t1);

            f[i][j][m] = f[i][j-1][0] + f[j][j][m];
            for(short p=pre[j]; p>=i; p=pre[p])
            {
                if((tmp = f[i][p][0] + f[p+1][j][0] + f[p][p][m]) < f[i][j][m])
				{
					f[i][j][m] = tmp;
				}
            }
			//clock_t t3 = clock();
			//sum2 += (t3 - t2);

            f[i][j][0] = f[i][j-1][0] + f[j][j][0];
			g[0][0] = f[i][j][0];
			s[0][0][i][j] = j - 1;
			memset(g, 0x3f, sizeof g);
			if(pre[j] != -1)
			{
				for(short k=1; k<m; ++k)
				{
					for(short c=max(1, m-k); c<m; ++c)
					{
						short e = max(i, s[k][c][i][pre[j]]);
						for(short p=min(pre[j], s[k][c][i+1][j]); p >= e; p=pre[p])
						{
							if((tmp = f[i][p][k] + f[p+1][j][c]) < g[k][c])
							{
								g[k][c] = tmp;
								if(tmp < f[i][j][0]) f[i][j][0] = tmp;
								s[k][c][i][j] = p;
							}
						}
					}
				}

				for(short p=pre[j]; p>=i; p=pre[p])
					if((tmp = min(f[i][p][0] + f[p+1][j][0], f[i][p][m] + f[p+1][j][m])) < f[i][j][0]) f[i][j][0] = tmp;
			}
			//clock_t t4 = clock();
			//sum3 += (t4 - t3);
        }
    }

	//printf("%dms %dms %dms\n", sum1, sum2, sum3);
	//printf("%dms\n", sum3);

	//printf("%d\n", f[4][5][1]);

    printf("%d\n", f[1][n][0]);
}

int main()
{
    while(scanf("%d", &m) != EOF)
    {
        //clock_t t1 = clock();
        init();
        solve();
        //clock_t t2 = clock();
        //printf("%d ms\n", t2 - t1);
    }
    return 0;
}

