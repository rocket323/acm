#include <stdio.h>
#include <cstring>
#define MaxL 201

int list[2][MaxL], t[2], n, m;
int g[MaxL][MaxL];
int ans[MaxL], sz;
int match;
int vis[MaxL], lik[MaxL], pos[MaxL];
int del[MaxL];

void init()
{
	scanf("%d%d", &n, &m);
	t[0] = t[1] = 0;
	for(int i=0; i<n; ++i)
	{
		int x;
		scanf("%d", &x);
		list[x][t[x]++] = i;
		pos[i] = x;
	}
	memset(g, 0, sizeof g);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
}

bool can(int now)
{
	for(int i=0; i<t[1]; ++i)
	{
		int p = list[1][i];
		if(del[p]) continue;
		if(!vis[p] && g[p][now])
		{
			vis[p] = 1;
			if(lik[p]==-1 || can(lik[p]))
			{
				lik[p] = now;
				return true;
			}
		}
	}
	return false;
}

int Max_Match()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=0; i<t[0]; ++i)
	{
		if(del[list[0][i]]) continue;
		memset(vis, 0, sizeof vis);
		if(can(list[0][i])) ans++;
	}
	return ans;
}

void out()
{
	if(sz==0) printf("0\n");
	else
	{
		printf("%d ", sz);
		for(int i=0; i<sz-1; ++i) printf("%d ", ans[i]);
		printf("%d\n", ans[sz-1]);
	}
}

void solve()
{
	memset(del, 0, sizeof del);
	match = Max_Match();
	sz = 0;
	for(int i=0; i<n; ++i)
	{
		del[i] = 1;
		
		int k = Max_Match();
		if(k < match) ans[sz++] = i, match = k;
		else del[i] = 0;
	}
	out();
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
