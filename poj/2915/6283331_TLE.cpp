#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define maxl 201
#define INF 0x3f3f
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

int n, m, f[maxl][maxl][22], pre[maxl], low[maxl][maxl][22];
int cnt[maxl], suf[maxl];
char T[maxl], S[maxl];

int max(int a, int b){ return (a > b) ? a : b; }

void init()
{
    scanf("%s", T);
    n = 0;
    for(int i=0; T[i]; ++i)
    {
        n++;
        cnt[n] = 1;
        S[n] = T[i];
        while(T[i+1] && T[i+1] == T[i]){ i++; cnt[n]++; }
    }

    memset(pre, -1, sizeof pre);
    for(int i=2; i<=n; ++i)
    {
        for(int j=i-1; j>=1; --j)
        {
            if(S[j] == S[i]){ pre[i] = j; break; }
        }
    }

    memset(suf, 0x3f, sizeof suf);
    for(int i=2; i<=n; ++i)
    {
        for(int j=1; j<i; ++j)
        {
            if(S[j] == S[i]){ suf[i] = j; break; }
        }
    }
}

void solve()
{
    memset(f, 0, sizeof f);
    for(int i=1; i<=n; ++i)
	{
		low[i][i][m] = INF;
        if(cnt[i] >= m) f[i][i][m] = 0;
        else f[i][i][m] = INF;

		for(int k=m-1; k>=1; --k)
		{
			if(k >= cnt[i]) f[i][i][k] = k - cnt[i];
            else f[i][i][k] = INF;
			low[i][i][k] = min(f[i][i][k], low[i][i][k+1]);
		}

		f[i][i][0] = go(cnt[i]);
        low[i][i][0] = f[i][i][0];
	}

    int tmp;
    for(int l=2; l<=n; ++l)
    {
        for(int i=1, j=i+l-1; j<=n; ++i, ++j)
        {
            for(int k=1; k<m; ++k)
            {
                f[i][j][k] = f[i][j-1][0] + f[j][j][k];
                for(int p=pre[j]; p>=i; p=pre[p])
                {
                    for(int c=0; c<=k; ++c)
                    {
                        if((tmp = f[i][p][c] + f[p+1][j][k-c]) < f[i][j][k]) f[i][j][k] = tmp;
                    }
                }
            }

            f[i][j][m] = f[i][j-1][0] + f[j][j][m];
            for(int p=pre[j]; p>=i; p=pre[p])
            {
                if((tmp = f[i][p][0] + f[p+1][j][0] + f[p][p][m]) < f[i][j][m]) f[i][j][m] = tmp;
            }

            f[i][j][0] = f[i][j-1][0] + f[j][j][0];
            for(int p=pre[j]; p>=i; p=pre[p])
            {
                for(int c=1; c<m; ++c)
                {
                    if((tmp = f[i][p][c] + low[p+1][j][m-c]) < f[i][j][0]) f[i][j][0] = tmp;
                }
                if((tmp = min(f[i][p][0] + f[p+1][j][0], f[i][p][m] + f[p+1][j][m])) < f[i][j][0]) f[i][j][0] = tmp; 
            }

            low[i][j][0] = f[i][j][0];
            low[i][j][m-1] = f[i][j][m-1];
            for(int x=m-2; x>=1; --x) low[i][j][x] = min(low[i][j][x+1], f[i][j][x]);

        }
    }
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

