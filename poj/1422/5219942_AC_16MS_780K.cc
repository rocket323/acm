#include <stdio.h>
#include <cstring>

int g[300][300], n, m;
int vis[300];
int lik[300];

void init()
{
	memset(g, 0, sizeof g);
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b+n] = g[b+n][a] = 1;
	}
}

bool can(int now)
{
	for(int i=n+1; i<=2*n; ++i)
	{
		if(!vis[i] && g[now][i])
		{
			vis[i] = 1;
			if(lik[i]==-1 || can(lik[i]))
			{
				lik[i] = now;
				return 1;
			}
		}
	}
	return 0;
}

void solve()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=n; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	ans = n - ans;
	printf("%d\n", ans);
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
