/*
 * =======================================================
 *       Filename:  3694.cpp
 *    Description:  
 *        Created:  28/10/10 00:09:21
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 100010

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], adj2[maxl], memo[maxl * 40];

int flag;
int n, m, mset, p[maxl], id[maxl], low[maxl], mark[maxl];
int tmp, vis[maxl], top, list[maxl], lv, q, sz, bridge[maxl * 10][2];

void addEdge(Edge adj[], int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

int find(int now)
{
	if(p[now] == now) return now;
	else return p[now] = find(p[now]);
}

void unionSet(int a, int b)
{
	int x = find(a), y = find(b);
	if(x != y) p[x] = y;
}

void dfs(int now, int pre)
{
	id[now] = low[now] = lv++;
	mark[now] = 1;

	bool flag = 0;
	for(Edge *ptr=adj2[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		if(!mark[v])
		{
			dfs(v, now);
			if(low[v] < low[now]) low[now] = low[v];
			if(low[v] <= id[now]) unionSet(now, v);
			else
			{
				bridge[sz][0] = now;
				bridge[sz++][1] = v;
			}
		}
		else
		{
			if(v != pre || flag) low[now] = min(low[now], low[v]);
			flag = 1;
		}
	}
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj2[i].next = adj[i].next = NULL;

	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(adj2, a, b);
		addEdge(adj2, b, a);
	}

	lv = sz = 0;
	for(int i=1; i<=n; ++i){ p[i] = i; mark[i] = 0; }
	dfs(1, -1);
	for(int i=1; i<=n; ++i) find(i);

	for(int i=1; i<=n; ++i)
	{
		for(Edge *ptr=adj2[i].next; ptr; ptr=ptr->next)
		{
			if(p[i] == p[ptr->idx]) continue;
			addEdge(adj, p[i], p[ptr->idx]);
		}
	}
}

void dfs2(int now, int t)
{
	if(now == t)
	{
		flag = 1;
		return;
	}
	vis[now] = 1;
	list[top++] = now;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		if(vis[v]) continue;

		if(find(now) != find(v))
		{
			tmp++;
			unionSet(find(now), find(v));
			dfs2(v, t);
			if(flag) return;
		}
		else
		{
			dfs2(v, t);
			if(flag) return;
		}
	}
}

void solve()
{
	int ans = sz;

	for(int i=1; i<=n; ++i) vis[i] = 0;
	scanf("%d", &q);
	for(int i=0; i<q; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(find(a) == find(b))
		{
			printf("%d\n", ans);
		}
		else
		{
			flag = 0;
			tmp = 0;
			top = 0;
			dfs2(find(a), find(b));
			for(int i=0; i<top; ++i) vis[list[i]] = 0;
			ans -= tmp;
			printf("%d\n", ans);
		}
	}
}

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), (n + m))
	{
		printf("Case %d:\n", ++tc);
		init();
		solve();
		puts("");
	}
	return 0;
}

