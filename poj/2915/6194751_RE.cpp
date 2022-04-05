#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define maxl 101
#define min(a,b) ((a<b)?a:b)

int n, m, f[maxl][maxl][26][21];
char S[maxl];

int max(int a, int b){ return (a>b)?a:b; }

int go(int len)
{
	if(len < m) return m - len;
	else return 1;
}

int find(int a, int end)
{
	while(a+1 <= end && S[a+1] == S[a]) a++;
	return a;
}

void solve()
{
	//printf("%s %d %d\n", S, n, m);

	memset(f, 0x3f, sizeof f);

	for(int i=0; i<=n; ++i) for(int j=0; j<i; ++j) for(int k=0; k<26; ++k) f[i][j][k][0] = 0;

	for(int i=1; i<=n; ++i)
	{
		int a = i;
		while(i+1 <= n && S[i+1] == S[a]) i++;
		int c = i - a + 1;
		if(c > m) c = m;
		f[a][i][S[a]-'A'][c] = 0;
		f[a][i][S[a]-'A'][0] = go(c);
	}

	for(int l=2; l<=n; ++l)
	{
		for(int i=1; i<=n-l+1; ++i)
		{
			int j = i + l - 1;
			for(int k=0; k<26; ++k)
			{
				for(int p=0; p<=min(l, m-1); ++p)
				{
					if(f[i][j][k][p] < INF) continue;

					for(int s=i; s<=j;)
					{
						int t = find(s, j);

						if(p == 0)
						{
							int t1 = f[i][s-1][k][0] + f[t+1][j][k][0];
							int t2 = INF;
							for(int x1=1; x1<=m; ++x1)
							{
								for(int x2=max(1, m-x1); x2<=m; ++x2)
									t2 = min(t2, f[i][s-1][k][x1] + f[t+1][j][k][x2]);
							}
							f[i][j][k][0] = min(f[i][j][k][0], min(t1, t2) + go(t - s + 1));
						}
						else
						{
							int flag = 0;
							if(i==1 && j==4 && k==0 && p==2) flag = 1;
							int tmp = INF;
							for(int x=0; x<=p; ++x) tmp = min(tmp, f[i][s-1][k][x] + f[t+1][j][k][p-x]);

							//if(flag) printf("here %d\n", tmp + go(t - s + 1));

							f[i][j][k][p] = min(f[i][j][k][p], tmp + go(t - s + 1));
						}

						s = t + 1;
					}

				}
			}
		}
	}

	//printf("n %d\n", f[1][4][0][2]);

	int ans = INF;
	for(int i=0; i<26; ++i) ans = min(ans, f[1][n][i][0]);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &m) != EOF)
	{
		scanf("%s", S+1);
		S[0] = '#';
		n = strlen(S) - 1;
		solve();
	}
}
