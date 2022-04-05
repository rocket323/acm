#include <stdio.h>
#include <cstring>

bool f[2010][1010];
int p[2010][1010], A[2010], top, v[2010], n, m, l, sum;

void solve()
{
	sum = 0;
	scanf("%d", &n);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &v[i]);
		sum += v[i];
	}

	memset(f, 0, sizeof f);
	f[0][0] = 1;

	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<=m; ++j)
		{
			if(f[i-1][j])
			{
				f[i][j] = 1;
				p[i][j] = j;
			}

			if(j>=v[i] && f[i-1][j-v[i]])
			{
				f[i][j] = 1;
				p[i][j] = j - v[i];
			}
		}
	}

	int ans = -1;
	for(int i=0; i<=m; ++i)
	{
		if(f[n][i] && sum-i<=l)
		{
			ans = i;
			break;
		}
	}

	if(ans == -1) puts("Impossible to distribute");
	else
	{
		top = 0;
		int x = ans;
		for(int i=n; i>=1; --i)
		{
			if(p[i][x] != x) A[top++] = i;
			x = p[i][x];
		}
		printf("%d", top);
		for(int i=top-1; i>=0; --i) printf(" %d", A[i]);
		puts("");
	}
}

int main()
{
	while(scanf("%d%d", &m, &l) && (m + l))
	{
		solve();
	}
}

