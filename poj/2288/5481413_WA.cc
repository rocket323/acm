#include <stdio.h>
#include <cstring>
#define ll long long
#define max(a,b) ((a>b)?a:b)

int sz[15], a, b, n, m;
int adj[13][13], g[13][13], v[13];
ll f[1<<13][13][13], cnt;

void init()
{
	memset(sz, 0, sizeof sz);
	memset(adj, 0, sizeof adj);
	scanf("%d%d", &n, &m);
	for(int i=0; i<n; ++i) scanf("%d", &v[i]);
	for(int i=0; i<m; ++i)
	{
		scanf("%d%d", &a, &b);
		a--, b--;
		g[a][sz[a]++] = b;
		g[b][sz[b]++] = a;
		adj[a][b] = adj[b][a] = 1;
	}
}

void solve()
{
	memset(f, -1, sizeof f);
	ll Max = 0, cnt = 0;

	if(n==1)
	{
		printf("%d %d\n", 0, 0);
		return;
	}

	for(int i=0; i<n; ++i)
	{
		for(int x=0; x<sz[i]; ++x)
		{
			int j = g[i][x];
			int tmp = ((1<<i) | (1<<j));

			f[tmp][i][j] = v[i] + v[j] + v[i] * v[j];
			
			if(i == (1<<n)-1)
			{
				if(f[tmp][i][j] > Max) Max = f[tmp][i][j], cnt = 1;
				else if(f[tmp][i][j] == Max) cnt++;
			}

		}
	}

	for(int i=0; i<(1<<n); ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(!(i & (1<<j))) continue;
			for(int x=0; x<sz[j]; ++x)
			{
				int k = g[j][x];
				if(!(i & (1<<k))) continue;
				if(f[i][j][k]==-1) continue;

				if(i == (1<<n)-1)
				{
					if(f[i][j][k] > Max) Max = f[i][j][k], cnt = 1;
					else if(f[i][j][k] == Max) cnt++;
				}

				for(int t=0; t<sz[k]; ++t)
				{
					int p = g[k][t];
					if(i & (1<<p)) continue;
					int tmp = v[p] + (ll)v[k] * v[p];
					if(adj[p][j]) tmp += (ll)v[j] * v[k] * v[p];

					f[i|(1<<p)][k][p] = max(f[i|(1<<p)][k][p], f[i][j][k] + tmp); 
				}
			}
		}
	}

	printf("%I64d %I64d\n", Max, cnt/2);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
