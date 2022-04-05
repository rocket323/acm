#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define maxl 205

short n, m, f[maxl][maxl][42], pre[maxl];
short cnt[maxl], sum[maxl];
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
		if(cnt[n] > m -1) cnt[n] = m - 1;
    }

    memset(pre, -1, sizeof pre);
    for(short i=2; i<=n; ++i)
    {
        for(short j=i-1; j>=1; --j)
        {
            if(S[j] == S[i]){ pre[i] = j; break; }
        }
    }

	memset(sum, 0, sizeof sum);
	for(int i=1; i<=n; ++i)
	{
		for(int j=i; j<=n; ++j)
		{
			if(S[i] == S[j]) sum[i] += cnt[j];
		}
		if(sum[i] > 2 * m - 1) sum[i] = 2 * m - 1;
	}
}

short append(short cnt, short k)
{
	int sum = cnt + k;
	if(sum >= m && k < m) return m - 1;
	else if(sum < 2 * m - 1) return k;
	else return 0;
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	for(short i=1; i<=n; ++i)
	{
		for(short j=0; j<2*m; ++j)
		{
			f[i][i][j] = max(0, m - j - cnt[i]);
			//printf("%d %d %d\n", i, j, f[i][i][j]);
		}
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(int k=0; k<=sum[j]; ++k)
			{

				/*
				int flag = 0;
				if(i == 3 && j == 7 && k == 0) flag = 1;
				*/

				f[i][j][k] = f[i][j-1][0] + max(0, m - k - cnt[j]);

				for(int p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = min(f[i][j][k], f[i][p][append(cnt[p], cnt[j] + k)] + f[p+1][j-1][0]);
					/*
					if(flag) printf("n %d %d %d %d\n", p, append(cnt[p], cnt[j]+k), f[i][p][append(cnt[p], cnt[j] + k)], f[p+1][j-1][0]);
					if(flag && p == 5)
					{
						printf("pp %d %d %d\n", cnt[p], cnt[j] + k, append(cnt[p], cnt[j] + k));
					}
					*/
				}
				//printf("%d %d %d %d\n", i, j, k, f[i][j][k]);
			}
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

