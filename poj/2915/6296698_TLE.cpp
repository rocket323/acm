#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define maxl 201
#define INF (n * m)
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

short n, m, f[maxl][maxl][22], pre[maxl], low[maxl][maxl][22];
short cnt[maxl], suf[maxl];
unsigned char r[22][22][maxl][maxl];
char T[maxl], S[maxl];

short max(short a, short b){ return (a > b) ? a : b; }

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
	memset(r, 0xff, sizeof r);
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
				r[a][b][i][i] = i;
	}

    short tmp;
    for(short l=2; l<=n; ++l)
    {
        for(short i=1, j=i+l-1; j<=n; ++i, ++j)
        {
            for(short k=1; k<m; ++k)
            {
                f[i][j][k] = f[i][j-1][0] + f[j][j][k];
				r[k][0][i][j] = j - 1;
                for(short c=0; c<=k; ++c)
                {

                	for(short p=min(pre[j], r[k][c][i+1][j]); p>=i && p >= r[k][c][i][pre[j]]; p=pre[p])
                    {
                        if((tmp = f[i][p][c] + f[p+1][j][k-c]) < f[i][j][k])
						{
							f[i][j][k] = tmp;
							r[k][c][i][j] = p;
						}
                    }
                }
            }

            f[i][j][m] = f[i][j-1][0] + f[j][j][m];
			//r[m][0][i][j] = j - 1;
            for(short p=pre[j]; p>=i; p=pre[p])
            {
                if((tmp = f[i][p][0] + f[p+1][j][0] + f[p][p][m]) < f[i][j][m])
				{
					f[i][j][m] = tmp;
					//r[k][c][i][j] = p;
				}
            }

            f[i][j][0] = f[i][j-1][0] + f[j][j][0];
            for(short p=pre[j]; p>=i; p=pre[p])
            {
                for(short c=1; c<m; ++c)
                {
                    if((tmp = f[i][p][c] + low[p+1][j][m-c]) < f[i][j][0])
					{
						f[i][j][0] = tmp;
					}
                }
                if((tmp = min(f[i][p][0] + f[p+1][j][0], f[i][p][m] + f[p+1][j][m])) < f[i][j][0]) f[i][j][0] = tmp;
            }

            low[i][j][0] = f[i][j][0];
            low[i][j][m-1] = f[i][j][m-1];
            for(short x=m-2; x>=1; --x) low[i][j][x] = min(low[i][j][x+1], f[i][j][x]);

        }
    }

	//printf("%d\n", f[2][3][1]);

    printf("%d\n", f[1][n][0]);
}

int main()
{
    while(scanf("%d", &m) != EOF)
    {
      
        init();
        solve();
  
    }
    return 0;
}

