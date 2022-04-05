#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define maxl 205

short n, m, f[maxl][maxl][42], pre[maxl];
short cnt[maxl], sum[maxl], nxt[26];
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

	memset(nxt, 0, sizeof nxt);
	for(int i=n; i>=1; --i)
	{
		int x = cnt[i] + nxt[S[i] - 'A'];
		if(x >= m && nxt[S[i] - 'A'] < m) x = m - 1 + cnt[i];
		else if(x >= 2 * m - 1) x = 2 * m - 2;

		sum[i] = nxt[S[i] - 'A'] = x;
	}
}

short append(short cnt, short k)
{
	int sum = cnt + k;
	if(sum >= m && k < m) return m - 1 + cnt;
	else if(sum < 2 * m - 1) return sum;
	else return cnt;
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	for(short i=1; i<=n; ++i)
	{
		for(short j=cnt[i]; j<2*m; ++j)
		{
			f[i][i][j] = max(0, m - j);
			//printf("%d %d %d\n", i, j, f[i][i][j]);
		}
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(int k=cnt[j]; k<=sum[j]; ++k)
			{

				/*
				int flag = 0;
				if(i == 1 && j == n && k == cnt[j]) flag = 1;
				*/

				f[i][j][k] = f[i][j-1][cnt[j-1]] + max(0, m - k);

				for(int p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = min(f[i][j][k], f[i][p][append(cnt[p], k)] + f[p+1][j-1][cnt[j-1]]);
					
					/*
					if(flag) printf("n %d %d %d %d\n", p, append(cnt[p], k), f[i][p][append(cnt[p], k)], f[p+1][j-1][cnt[j-1]]);
					if(flag && p == 5)
					{
						printf("pp %d %d %d\n", cnt[p], k, append(cnt[p], k));
					}
					*/
					
				}
				//printf("%d %d %d %d\n", i, j, k, f[i][j][k]);
			}
		}
	}

	printf("%d\n", f[1][n][cnt[n]]);
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

