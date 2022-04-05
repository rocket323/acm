#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define MaxL 201
#define INF 0x3f3f
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

int n, m, f[MaxL][MaxL][22], pre[MaxL], low[MaxL][MaxL][22];
int cnt[MaxL], suf[MaxL];
unsigned char r[22][22][MaxL][MaxL], s[MaxL][MaxL];
char T[MaxL], S[MaxL];

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
}

void solve()
{
    memset(f, 0, sizeof f);
	memset(r, 0xff, sizeof r);
	memset(s, 0xff, sizeof s);
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

		for(int a=0; a<=m; ++a)
			for(int b=0; b<=m; ++b)
				r[a][b][i][i] = i;
		s[i][i] = i;
	}

    int tmp;
    for(int l=2; l<=n; ++l)
    {
        for(int i=1, j=i+l-1; j<=n; ++i, ++j)
        {
            for(int k=1; k<=m; ++k)
            {
                f[i][j][k] = f[i][j-1][0] + f[j][j][k];
				r[k][0][i][j] = j - 1;
                for(int c=0; c<=k; ++c)
                {
                	for(int p=min(pre[j], r[k][c][i+1][j]); p>=i && p >= r[k][c][i][pre[j]]; p=pre[p])
                    {
                        if((tmp = f[i][p][c] + f[p+1][j][k-c]) < f[i][j][k])
						{
							f[i][j][k] = tmp;
							r[k][c][i][j] = p;
						}
                    }
                }
            }

			/*
            f[i][j][m] = f[i][j-1][0] + f[j][j][m];
			r[m][0][i][j] = j - 1;
            for(int p=pre[j]; p>=i; p=pre[p])
            {
                if((tmp = f[i][p][0] + f[p+1][j][0] + f[p][p][m]) < f[i][j][m])
				{
					f[i][j][m] = tmp;
					r[m][0][i][j] = p;
				}
            }
			*/

            f[i][j][0] = f[i][j-1][0] + f[j][j][0];
			s[i][j] = j - 1;
            
			for(int c=1; c<m; ++c)
            {
                for(int p=min(pre[j], s[i+1][j]); p>=i && p >= s[i][pre[j]]; p=pre[p])
                {
                    if((tmp = f[i][p][c] + low[p+1][j][m-c]) < f[i][j][0])
					{
						f[i][j][0] = tmp;
						s[i][j] = p;
					}
                }
            }

			for(int p=min(pre[j], s[i+1][j]); p>=i && p >= s[i][pre[j]]; p=pre[p])
			{
                if((tmp = f[i][p][0] + f[p+1][j][0]) < f[i][j][0])
				{
					f[i][j][0] = tmp;
					s[i][j] = p;
				}
			}

			for(int p=min(pre[j], s[i+1][j]); p>=i && p >= s[i][pre[j]]; p=pre[p])
			{
                if((tmp = f[i][p][m] + f[p+1][j][m]) < f[i][j][0])
				{
					f[i][j][0] = tmp;
					s[i][j] = p;
				}
			}

            low[i][j][0] = f[i][j][0];
            low[i][j][m-1] = f[i][j][m-1];
            for(int x=m-2; x>=1; --x) low[i][j][x] = min(low[i][j][x+1], f[i][j][x]);

        }
    }

	//printf("%d %d %d\n", f[4][5][1], r[0][2][1][3], r[0][2][2][5]);

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

