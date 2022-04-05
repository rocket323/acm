/*
 * =======================================================
 *       Filename:  3713.cpp
 *    Description:  
 *        Created:  24/10/10 21:18:50
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 205
#define maxe 20010

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxe * 4];

int n, m, mset, id[maxl], low[maxl], mark[maxl], del[maxl], lv;
int bc, cnt;

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<n; ++i) adj[i].next = NULL;

	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void dfs(int now, int pre)
{
	cnt++;
	if(del[now]) return;
	id[now] = low[now] = lv++;
	mark[now] = 1;

	int flag = 0;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int v = ptr->idx;
		if(del[v]) continue;
		if(!mark[v])
		{
			dfs(v, now);
			if(low[v] < low[now]) low[now] = low[v];

			if(low[v] >= id[now]) bc++;
		}
		else
		{
			if(v != pre || v == pre && flag)
			{
				if(id[v] < low[now]) low[now] = id[v];
			}
			flag = 1;
		}
	}
}

bool check()
{
	for(int i=0; i<n; ++i){ mark[i] = 0; }
	lv = 0;
	bc = 0;
	for(int i=0; i<n; ++i)
	{
		if(mark[i]) continue;
		dfs(i, -1);
		//if(isCut[i]) return 1;
	}
	return bc > 2;
}

bool solve()
{
	cnt = 0;
	dfs(0, -1);
	if(cnt < n) return 0;
	memset(del, 0, sizeof del);
	for(int i=0; i<n; ++i)
	{
		del[i] = 1;
		if(check()) return 0;
		del[i] = 0;
	}
	return 1;
}

int main()
{
	while(scanf("%d%d", &n, &m), (n + m))
	{
		init();
		puts(solve() ? "YES" : "NO");

	}
	return 0;
}

