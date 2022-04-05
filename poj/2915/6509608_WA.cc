#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define maxl 201
#define INF 0x3f3f3f3f
#define go(x) (((x)<m)?(m-(x)):1)

short n, m, f[maxl][maxl][22], pre[maxl], low[maxl][maxl][22];
short cnt[maxl], suf[maxl];
char T[maxl], S[maxl];

short max(short a, short b){ return (a > b) ? a : b; }
short min(short a, short b){ return (a < b) ? a : b; }

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

short calc(short x)
{
	if(x < m) return m - x;
	else if(x == m) return 1;
	else return 0;
}

void solve()
{
	memset(f, 0, sizeof f);
	for(short i=1; i<=n; ++i)
	{
		for(short j=0; j<=m; ++j)
		{
			if(cnt[i] + j < m) f[i][i][j] = m - (cnt[i] + j);
			else if(j == 0) f[i][i][j] = 1;
			else f[i][i][j] = 0;
		}
	}

	for(short l=2; l<=n; ++l)
	{
		for(short i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(short k=0; k<=m; ++k)
			{

				short flag = 0;
				if(i == 2 && j == 8 && k == 0) flag = 1;
				
				short num = cnt[j] + k;
				if(num >= m)
				{
					if(k == 0) num = m;
					else num = 0;
				}

				if(cnt[j] + k < m) f[i][j][k] = f[i][j-1][0] + m - (cnt[j] + k);
				else if(cnt[j] + k >= m && k == 0) f[i][j][k] = f[i][j-1][0] + 1;
				else f[i][j][k] = f[i][j-1][0];

				for(short p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = min(f[i][j][k], f[i][p][num] + f[p+1][j-1][0]);
					//if(flag) printf("n %d %d %d %d\n", p, num, f[i][p][num], f[p+1][j-1][0]);
				}
				
				//if(flag) printf("h %d\n", f[i][j-1][0]);

				//printf("%d %d %d %d\n", i, j, k, f[i][j][k]);
			}
		}
	}

	//for(int i=1; i<=n; ++i) printf("%c %d\n", S[i], cnt[i]);

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

