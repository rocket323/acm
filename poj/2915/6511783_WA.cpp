#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define Maxl 205
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

short n, m, f[Maxl][Maxl][42], pre[Maxl];
short cnt[Maxl], sum[Maxl], nxt[26], Ap[Maxl][Maxl];
char T[Maxl], S[Maxl];

void init()
{
    scanf("%s", T);

	int len = strlen(T);
	for(int i=0; i<=len/2; ++i)
	{
		char tmp;
		tmp = T[i], T[i] = T[len-1-i], T[len-1-i] = tmp;
	}

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

short inline append(short cnt, short k)
{
	short sum = cnt + k;
	if(sum >= m && k < m) return m - 1 + cnt;
	else if(sum < 2 * m - 1) return sum;
	else return cnt;
}

void solve()
{

	for(int i=0; i<Maxl; ++i) for(int j=0; j<Maxl; ++j) Ap[i][j] = append(i, j);

	memset(f, 0x3f, sizeof f);
	for(short i=1; i<=n; ++i)
	{
		for(short j=cnt[i]; j<2*m; ++j)
		{
			f[i][i][j] = max(0, m - j);
		}
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1, j=i+l-1; j<=n; ++i, ++j)
		{
			for(int k=cnt[j]; k<=sum[j]; ++k)
			{

				f[i][j][k] = f[i][j-1][cnt[j-1]] + max(0, m - k);

				for(int p=pre[j]; p>=i; p=pre[p])
				{
					f[i][j][k] = min(f[i][j][k], f[i][p][Ap[cnt[p]][k]] + f[p+1][j-1][cnt[j-1]]);
				}
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

