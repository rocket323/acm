/*
 * =======================================================
 *       Filename:  1364.cpp
 *    Description:  
 *        Created:  08/09/10 16:29:30
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 1010
#define maxe 3010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[maxe];

int mset, n, m, d[maxl], a, b, c;
char str[3];

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=0; i<m; ++i)
	{
		scanf("%d%d%s%d", &a, &b, str, &c);
		if(str[0] == 'l')
			addEdge(a - 1, a + b - 1, c - 1);
		else
			addEdge(a + b - 1, a - 1, -c - 1);
	}
}

bool solve()
{
	for(int i=0; i<=n; ++i) d[i] = INF;
	d[0] = 0;

	for(int x=0; x<=n; ++x)
	{
		for(int i=0; i<=n; ++i)
		{
			for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
			{
				int v = ptr->idx;
				if(d[i] + ptr->len < d[v])
					d[v] = d[i] + ptr->len;
			}
		}
	}
	for(int i=0; i<=n; ++i)
	{
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(d[i] + ptr->len < d[v]) return 0;
		}
	}
	return 1;
}

int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		init();
		puts(solve() ? "lamentable kingdom" : "successful conspiracy");
	}
	return 0;
}

