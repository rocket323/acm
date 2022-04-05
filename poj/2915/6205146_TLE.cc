#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define maxl 205

int n, m, cnt[maxl], f[maxl][maxl][23];
char S[maxl], T[maxl];

int max(int a, int b){ return (a > b) ? a : b; }
int min(int a, int b){ return (a < b) ? a : b; }
int go(int x){ return (x < m) ? m - x : 1; }

void init()
{
	scanf("%s", T);
	n = 0;
	int len = strlen(T);

	for(int i=0; T[i]; ++i)
	{
		n++;
		S[n] = T[i];
		cnt[n] = 1;
		while(i+1 < len && T[i+1] == T[i]){ i++; cnt[n]++; }
	}
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	
	for(int i=1; i<=n; ++i)
	{
		for(int k=0; k<=m; ++k)
		{
			if(cnt[i] + k < m) f[i][i][k] = m - (cnt[i] + k);
			else if(k == 0) f[i][i][k] = 1;
			else f[i][i][k] = 0;
		}
	}

	//for(int i=1; i<=n; ++i) printf("%c %d\n", S[i], cnt[i]);

	for(int l=2; l<=n; ++l)
	{
		for(int i=1; i<=n-l+1; ++i)
		{
			int j = i + l - 1;
			for(int k=0; k<=m; ++k)
			{
				if(cnt[j] + k >= m && k != 0)
				{
					f[i][j][k] = f[i][j-1][0];
				}
				else
				{
					f[i][j][k] = f[i][j-1][0] + go(cnt[j]);

					for(int p=i; p<j; ++p)
					{
						if(S[p] != S[j]) continue;
						int tmp = cnt[j] + k;
						if(tmp > m) tmp = m;
						f[i][j][k] = min(f[i][j][k], f[i][p][tmp] + f[p+1][j-1][0]);
					}
				}
			}
		}
	}

	//printf("n %d %d\n", f[1][1][1], f[2][6][0]);
	
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

