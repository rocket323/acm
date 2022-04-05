/*
 * =======================================================
 *       Filename:  1129.cpp
 *    Description:  dfs
 *        Created:  25/08/10 16:12:16
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

char str[100];
int vis[100][10], flag, n;
vector<int> adj[100];

void init()
{
	for(int i=0; i<n; ++i) adj[i].clear();
	for(int i=0; i<n; ++i)
	{
		scanf("%s", str);
		for(int j=0; str[j+2]; ++j)
		{
			char ch = str[j+2];
			adj[i].push_back(ch - 'A');
		}
	}

	/*
	for(int i=0; i<n; ++i)
	{
		printf("%d : ", i);
		for(int j=0; j<adj[i].size(); ++j) printf("%d ", adj[i][j]);
		puts("");
	}
	*/
}

void dfs(int now, int dep, int mx)
{
	if(flag) return;

	if(now == n)
	{
		flag = 1;
		return;
	}

	if(mx > dep) return;

	for(int i=1; i<=mx; ++i)
	{
		if(vis[now][i]) continue;
		for(int j=0; j<adj[now].size(); ++j)
		{
			int k = adj[now][j];
			vis[k][i]++;
		}

		dfs(now + 1, dep, mx);

		if(flag) return;
		
		for(int j=0; j<adj[now].size(); ++j)
		{
			int k = adj[now][j];
			vis[k][i]--;
		}
	}

	if(mx == dep) return;

	for(int j=0; j<adj[now].size(); ++j)
	{
		int k = adj[now][j];
		vis[k][mx+1]++;
	}

	dfs(now + 1, dep, mx + 1);

	if(flag) return;
	
	for(int j=0; j<adj[now].size(); ++j)
	{
		int k = adj[now][j];
		vis[k][mx+1]--;
	}
}

int solve()
{
	for(int i=1; i<=4; ++i)
	{
		flag = 0;
		memset(vis, 0, sizeof vis);
		dfs(0, i, 0);
		if(flag) return i;
	}
}

int main()
{
	while(scanf("%d\n", &n), n)
	{
		init();
		int k = solve();
		if(k == 1) puts("1 channel needed.");
		else printf("%d channels needed.\n", k);
	}
	return 0;
}

