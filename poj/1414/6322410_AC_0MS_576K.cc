#include <stdio.h>
#include <cstring>
#define INF 0x3f3f3f3f
#define max(a,b) ((a>b)?a:b)

int n, a[20][20], vis[20][20], c;
int dr[6] = {-1, -1, 0, 1, 1, 0};
int dc[6] = {-1, 0, 1, 1, 0, -1};

void init()
{
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j) scanf("%d", &a[i][j]);
	}

	/*
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j) printf("%d ", a[i][j]);
		puts("");
	}
	*/
}

void dfs(int r, int c)
{
	vis[r][c] = 1;
	for(int i=0; i<6; ++i)
	{
		int rr = r + dr[i];
		int cc = c + dc[i];
		if(rr >= 1 && rr <= n && cc >= 1 && cc <= rr)
		{
			if(vis[rr][cc] == 1) continue;

			if(a[r][c] == 0 || a[r][c] == a[rr][cc])
				dfs(rr, cc);
		}
	}
}

int go(int s, int t)
{
	memset(vis, 0, sizeof vis);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j)
		{
			if(a[i][j] != 0) continue;
			dfs(i, j);
		}
	}
	int ans = 0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j)
		{
			if(!vis[i][j])
			{
				if(a[i][j] == c) ans--;
				else ans++;
			}
		}
	}
	return ans;
}

void solve()
{
	int ans = -INF;
	
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j)
		{
			if(a[i][j] != 0) continue;
			a[i][j] = c;
			int k = go(i, j);
			ans = max(ans, k);
			a[i][j] = 0;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &c), (n+c))
	{
		init();
		solve();
	}
	return 0;
}

