#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define maxl 201
#define INF 0x3f3f
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

short n, m, f[maxl][maxl][22], pre[maxl], low[maxl][maxl][22];
short cnt[maxl];
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
	}

    for(short l=2; l<=n; ++l)
    {
        for(short i=1, j=i+l-1; j<=n; ++i, ++j)
        {

            for(short k=1; k<=m; ++k)
            {
                f[i][j][k] = f[i][j-1][0] + f[j][j][k];
                for(int p=pre[j]; p>=i && p!=-1; p=pre[p])
                {
                    for(short c=0; c<=k; ++c)
                    {
                        f[i][j][k] = min(f[i][j][k], f[i][p][c] + f[p+1][j][k-c]);
                    }
                }
            }

            f[i][j][0] = f[i][j-1][0] + f[j][j][0];
            for(short p=pre[j]; p>=i && p!=-1; p=pre[p])
            {
                for(short c=1; c<m; ++c)
                {
                    f[i][j][0] = min(f[i][j][0], f[i][p][c] + low[p+1][j][m-c]);
                }
                short a = min(f[i][p][0] + f[p+1][j][m] + 1, f[i][p][0] + f[p+1][j][0]);
                short b = min(f[i][p][m] + f[p+1][j][0] + 1, f[i][p][m] + f[p+1][j][m]);
                f[i][j][0] = min(f[i][j][0], min(a, b));
            }

            low[i][j][0] = f[i][j][0];
            low[i][j][m-1] = f[i][j][m-1];
            for(short x=m-2; x>=1; --x) low[i][j][x] = min(low[i][j][x+1], f[i][j][x]);

        }
    }
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

