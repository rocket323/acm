#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxl 220

vector<int> adj[maxl];
int mset, w[maxl];
int f[maxl][maxl][2], g[maxl][maxl][2], n, k, p[maxl], ans;

void init()
{
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].clear();

	for(int i=1; i<=n; ++i) scanf("%d", &w[i]);
	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}

void dp(int now)
{
	int idx = 0;

	memset(g, 0, sizeof g);

	for(int x=0; x<adj[now].size(); x++)
	{
		int v = adj[now][x];
		if(p[now] == v) continue;
		p[v] = now;
		dp(v);
	}

	for(int c=0; c<adj[now].size(); c++)
	{
		int v = adj[now][c];
		idx++;

		for(int j=0; j<=k; ++j)
		{

			g[idx][j][0] = g[idx-1][j][0];
			g[idx][j][1] = g[idx-1][j][1];

			for(int x=0; x<=j-2; ++x)
			{
				g[idx][j][0] = max(g[idx][j][0], g[idx-1][x][0] + f[v][j-2-x][0]);
				g[idx][j][1] = max(g[idx][j][1], g[idx-1][x][1] + f[v][j-2-x][0]);
			}
			for(int x=0; x<=j-1; ++x)
			{
				g[idx][j][1] = max(g[idx][j][1], g[idx-1][x][0] + f[v][j-1-x][1]);
			}
		}
	}

	for(int i=0; i<=k; ++i)
	{
		f[now][i][0] = g[idx][i][0] + w[now];
		f[now][i][1] = g[idx][i][1] + w[now];
	}
}

void solve()
{
	memset(p, -1, sizeof p);
	memset(f, 0, sizeof f);

	dp(1);

	ans = 0;
	for(int i=0; i<=k; ++i) ans = max(ans, max(f[1][i][0], f[1][i][1]));
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &k) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

