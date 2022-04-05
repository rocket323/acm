#include <stdio.h>
#include <cstring>
#define INF 0x7f7f7f7f
#define MaxL 101

int g[MaxL][MaxL], n;
int d[MaxL];
int Q[MaxL];

void init()
{
	scanf("%d", &n);
	memset(g, 0, sizeof g);
	memset(d, 0, sizeof d);
	for(int i=1; i<=n; ++i)
	{
		int a;
		while(scanf("%d", &a) && a)
		{
			g[i][a] = 1;
			d[a]++;
		}
	}
}

void solve()
{
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			if(d[j]==0)
			{
				d[j] = INF;
				Q[i] = j;
				for(int k=1; k<=n; ++k)
					if(g[j][k]) d[k]--;
				break;
			}
		}
	}
	for(int i=1; i<n; ++i) printf("%d ", Q[i]);
	printf("%d\n", Q[n]);
}

int main()
{
	init();
	solve();
	return 0;
}