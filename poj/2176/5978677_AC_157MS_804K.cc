#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define maxl 150
#define min(a,b) ((a<b)?a:b)

int d[maxl];
int n, p[maxl], g[maxl][maxl], f[maxl][maxl], sp[maxl][maxl];
char S[maxl];

int check(char S[], int n)
{
	memset(p, -1, sizeof p);
	p[0] = -1;
	int j = -1;

	for(int i=1; i<n; ++i)
	{
		while(j > -1 && S[j+1] != S[i]) j = p[j];
		if(S[j+1] == S[i]) j++;
		p[i] = j;
	}

	if(n == 1) return 1;

	return ((p[n - 1] != -1 && n % (n - 1 - p[n - 1]) == 0) ? n - 1 - p[n - 1] : -1);
}

int calc(int n)
{
	int ans = 0;
	while(n)
	{
		ans++;
		n /= 10;
	}
	return ans;
}

void init()
{
	n = strlen(S);
	for(int i=0; i<n; ++i)
	{
		for(int j=i; j<n; ++j)
		{
			g[i][j] = check(S+i, j-i+1);
		}
	}
}

void out(int a, int b)
{
	if(sp[a][b] == -1)
	{
		for(int i=a; i<=b; ++i) printf("%c", S[i]);
		return;
	}

	if(g[a][b] != -1)
	{
		int l = b - a + 1;
		int k = g[a][b];
		printf("%d(", l/k);
		out(a, a+k-1);
		printf(")");
	}
	else
	{
		int k = sp[a][b];
		out(a, k);
		out(k+1, b);
	}
}

void solve()
{
	memset(sp, -1, sizeof sp);
	memset(f, 0x3f, sizeof f);
	for(int i=0; i<n; ++i) f[i][i] = 1;

	for(int l=2; l<=n; ++l)
	{
		for(int i=0; i<=n-l; ++i)
		{
			int j = i + l - 1;

			f[i][j] = l;
			if(g[i][j] == -1)
			{
				for(int k=i; k<j; ++k)
				{
					int tmp = f[i][k] + f[k+1][j];
					if(tmp < f[i][j])
					{
						sp[i][j] = k;
						f[i][j] = tmp;
					}
				}
			}
			else
			{
				int t = g[i][j];
				for(int k=t; k<=l; k+=t)
				{
					if(l % k) continue;

					int tmp = f[i][i+k-1] + d[l/k] + 2;
					if(tmp < f[i][j])
					{
						sp[i][j] = k;
						f[i][j] = tmp;
					}
				}
			}
		}
	}

	out(0, n-1);
	puts("");
}

int main()
{
	while(scanf("%s", S) != EOF)
	{
		for(int i=1; i<maxl; ++i) d[i] = calc(i);
		init();
		solve();
	}
	return 0;
}

