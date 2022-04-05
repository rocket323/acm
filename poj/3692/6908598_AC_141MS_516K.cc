#include <stdio.h>
#include <cstring>

int g, b, m, adj[205][205];
int lik[205], vis[205];

void init()
{
	memset(adj, 0, sizeof adj);
	for(int i=1; i<=m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a][b] = 1;
	}
	for(int i=1; i<=g; ++i) for(int j=1; j<=b; ++j) adj[i][j] ^= 1;
}

bool can(int now)
{
	for(int i=1; i<=b; ++i)
	{
		if(adj[now][i] && !vis[i])
		{
			vis[i] = 1;
			if(lik[i] == -1 || can(lik[i]))
			{
				lik[i] = now;
				return 1;
			}
		}
	}
	return 0;
}

int max_match()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=g; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	return ans;
}

int main()
{
	int tc = 0;
	while(scanf("%d%d%d", &g, &b, &m), (g + b + m))
	{
		printf("Case %d: ", ++tc);
		init();
		printf("%d\n", g + b - max_match());
	}
	return 0;
}

