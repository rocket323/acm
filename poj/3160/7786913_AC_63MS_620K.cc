/*
 * =======================================================
 *       Filename:  3160.cpp
 *    Description:  
 *        Created:  25/10/10 10:03:17
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 40010
#define UNVIS 0
#define VIS 1
#define OVER 2

struct Edge
{
	int idx;
	Edge *next;
}
adj0[maxl], adj1[maxl], memo[4000010];

int n, m, v[maxl], mset, id[maxl], low[maxl], st[maxl], top;
int f[maxl], mark[maxl], lv, p[maxl], ans, mv, an;

void addEdge(Edge adj[], int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<n; ++i) adj0[i].next = adj1[i].next = NULL;
	mv = -1000000000;
	an = 1;
	for(int i=0; i<n; ++i)
	{
		scanf("%d", &v[i]);
		if(v[i] > mv) mv = v[i];
		if(v[i] >= 0) an = 0;
	}
	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(adj0, a, b);
	}
}

void dfs(int now)
{
	id[now] = low[now] = lv++;
	mark[now] = VIS;
	st[++top] = now;

	for(Edge *ptr=adj0[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		if(mark[v] == UNVIS)
		{
			dfs(v);
			if(low[v] < low[now]) low[now] = low[v];
		}
		else if(mark[v] == VIS)
		{
			if(low[v] < low[now]) low[now] = low[v];
		}
	}

	if(low[now] == id[now])
	{
		do
		{
			mark[st[top]] = OVER;
			p[st[top]] = now;
		}
		while(st[top--] != now);
	}
}

int dp(int now)
{
	if(f[now] != -1) return f[now];
	f[now] = v[now];
	int tmp = 0;
	for(Edge *ptr=adj1[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		tmp = max(tmp, dp(v));
	}
	return f[now] = tmp + f[now];
}

void solve()
{
	for(int i=0; i<n; ++i) mark[i] = UNVIS;
	lv = top = 0;
	for(int i=0; i<n; ++i)
	{
		if(mark[i] == 0) dfs(i);
	}

	for(int i=0; i<n; ++i)
	{
		for(Edge *ptr=adj0[i].next; ptr; ptr=ptr->next)
		{
			if(p[i] == p[ptr->idx]) continue;
			addEdge(adj1, p[i], p[ptr->idx]);
		}
	}

	for(int i=0; i<n; ++i)
	{
		if(v[i] < 0) v[i] = 0;
		f[i] = -1;
		if(p[i] != i) v[p[i]] += v[i];
	}

	ans = 0;
	for(int i=0; i<n; ++i)
	{
		if(p[i] != i) continue;
		ans = max(ans, dp(i));
	}
	//if(an) ans = mv;
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

