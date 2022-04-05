/*
 * =======================================================
 *       Filename:  3216.cpp
 *    Description:  
 *        Created:  15/10/10 20:21:55
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 305
#define INF 0x3f3f3f3f

int n, m, t[maxl], p[maxl], l[maxl], d[50][50];
int vis[maxl], lik[maxl];
vector<int> adj[maxl];

void init()
{
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j)
	{
		scanf("%d", &d[i][j]);
		if(d[i][j] == -1) d[i][j] = INF;
	}
	for(int k=1; k<=n; ++k)
	{
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		}
	}
}

bool can(int now)
{
	for(int i=0; i<adj[now].size(); ++i)
	{
		int k = adj[now][i];
		if(vis[k]) continue;
		vis[k] = 1;
		if(lik[k] == -1 || can(lik[k]))
		{
			lik[k] = now;
			return 1;
		}
	}
	return 0;
}

void solve()
{
	for(int i=1; i<=m; ++i) scanf("%d%d%d", &p[i], &t[i], &l[i]);

	/*
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j) printf("%d ", d[i][j]);
		puts("");
	}
	*/

	for(int i=1; i<=m; ++i) adj[i].clear();
	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			if(i == j) continue;
			int len = d[p[i]][p[j]];
			if(t[i] + len + l[i] > t[j]) continue;
			adj[i].push_back(j + m);
			printf("n %d %d\n", i, j);
		}
	}

	int ans = m;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=m; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans--;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m), (n + m))
	{
		init();
		solve();
	}
	return 0;
}

