/*
 * =======================================================
 *       Filename:  1909.cpp
 *    Description:  
 *        Created:  19/10/10 21:28:09
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxl 10010

int cnt[maxl], sz[maxl], cc[maxl], f[maxl], d[maxl], n, id, num[maxl], k;
vector<int> adj[maxl];

void init()
{
	memset(d, 0, sizeof d);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &id);
		adj[id].clear();
		scanf("%d%d", &num[id], &cc[id]);
		for(int j=0; j<cc[id]; ++j)
		{
			scanf("%d", &k);
			adj[id].push_back(k);
			d[k]++;
		}
	}
}

void dp(int now)
{
	cnt[now] = num[now];
	sz[now] = 1;
	for(int i=0; i<adj[now].size(); ++i)
	{
		int k = adj[now][i];
		dp(k);
		cnt[now] += cnt[k];
		sz[now] += sz[k];
	}

	f[now] = abs(sz[now] - cnt[now]);
	for(int i=0; i<adj[now].size(); ++i)
	{
		int k = adj[now][i];
		f[now] += f[k];
	}
}

void solve()
{
	for(int i=1; i<=n; ++i)
	{
		if(d[i]) continue;
		dp(i);
		printf("%d\n", f[i]);
		break;
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

