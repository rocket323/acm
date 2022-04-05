#include <stdio.h>
#include <cstring>
#define INF 0x3f3f
#define MaxL 205
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
#define go(x) (((x)<m)?(m-(x)):1)

short n, m, cnt[MaxL], f[MaxL][MaxL][23], pre[MaxL], low[MaxL][MaxL][23];
char S[MaxL], T[MaxL];

void init()
{
	//scanf("%s", T);
	gets(T);

	for(int i=0; T[i]; ++i) if(!(T[i] >= 'A' && T[i] <= 'Z')) while(1);

	n = 0;
	int len = strlen(T);

	for(int i=0; T[i]; ++i)
	{
		n++;
		S[n] = T[i];
		cnt[n] = 1;
		while(i+1 < len && T[i+1] == T[i]){ i++; cnt[n]++; }
	}

	memset(pre, -1, sizeof pre);
	for(int i=1; i<=n; ++i)
	{
		pre[i] = -1;
		for(int j=i-1; j>=1 && pre[i]==-1; --j)
		{
			if(S[i] == S[j]) pre[i] = j;
		}
	}
}

void solve()
{
	memset(f, 0x3f, sizeof f);

	//for(int i=1; i<=n; ++i) printf("%c %d\n", S[i], cnt[i]);

	for(int i=1; i<=n; ++i)
	{
		low[i][i][m+1] = INF;
		for(int k=m; k>=1; --k)
		{
			if(k >= cnt[i]) f[i][i][k] = k - cnt[i];
			low[i][i][k] = min(f[i][i][k], low[i][i][k+1]);
		}
		f[i][i][0] = go(cnt[i]);
	}

	/*
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<i; ++j)
		{
			for(int k=0; k<=m; ++k) f[i][j][k] = 0;
		}
	}
	*/

	//f[i][j][k] :  区间[i, j] 消成K个S[j]的最小步数

	for(int l=2; l<=n; ++l)
	{
		for(int i=1; i<=n-l+1; ++i)
		{
			int j = i + l - 1;

			for(int p=j; p>=i && p!=-1; p=pre[p])
			{	
				for(int k=m-1; k>0 && k>=cnt[j]; --k)
				{
					if(p == j) f[i][j][k] = min(f[i][j][k], f[i][j-1][0] + k - cnt[j]);
					f[i][j][k] = min(f[i][j][k], f[i][p][k-cnt[j]] + f[p+1][j-1][0]);
				}

				int c = cnt[j] >= m ? m - 1 : cnt[j];
				int tmp = low[i][p][m-c] + f[p+1][j-1][0];
				f[i][j][0] = min(f[i][j][0], tmp);

				if(cnt[j] >= m) f[i][j][0] = min(f[i][j][0], f[i][p][0] + f[p+1][j-1][0] + 1);

				if(p == j) f[i][j][0] = min(f[i][j][0], f[i][j-1][0] + go(cnt[j]));
			}

			low[i][j][m] = f[i][j][m];
			for(int k=m-1; k>=1; --k) low[i][j][k] = min(f[i][j][k], low[i][j][k+1]);

		}
	}

	if(f[1][n][0] >= INF) while(1);

	printf("%d\n", f[1][n][0]);
}

int main()
{
	while(scanf("%d\n", &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}
