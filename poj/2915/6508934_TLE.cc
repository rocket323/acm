#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#define maxl 201
#define INF 0x3f3f3f3f
#define go(x) (((x)<m)?(m-(x)):1)

int n, m, f[maxl][maxl][22], pre[maxl], low[maxl][maxl][22];
int cnt[maxl], suf[maxl];
char T[maxl], S[maxl];

int max(int a, int b){ return (a > b) ? a : b; }
int min(int a, int b){ return (a < b) ? a : b; }

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

int calc(int x)
{
	if(x < m) return m - x;
	else return 0;
}

void solve()
{
	memset(f, 0, sizeof f);
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<=m; ++j)
		{
			f[i][i][j] = calc(cnt[i] + j);
		}
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(int k=0; k<=m; ++k)
			{
				f[i][j][k] = f[i][j-1][0] + calc(cnt[j] + k);

				int flag = 0;
				if(i == 1 && j == n && k == 0) flag = 1;
				
				int num = cnt[j] + k;
				if(num > m) num = 0;
				for(int p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = min(f[i][j][k], f[i][p][num] + f[p+1][j-1][0]);
					//if(flag) printf("%d %d %d %d\n", p, num, f[i][p][num], f[p+1][j-1][0]);
				}
			}
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

