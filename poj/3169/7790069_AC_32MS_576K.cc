/*
 * =======================================================
 *       Filename:  3169.cpp
 *    Description:  
 *
 *        Created:  25/10/10 22:20:31
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 2010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[400010];

int n, ml, md, d[maxl], cnt[maxl], in[maxl], Q[maxl * 1000];
int head, tail, mset;

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
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	int a, b, d;
	for(int i=0; i<ml; ++i)
	{
		scanf("%d%d%d", &a, &b, &d);
		addEdge(a, b, d);
	}
	for(int i=0; i<md; ++i)
	{
		scanf("%d%d%d", &a, &b, &d);
		addEdge(b, a, -d);
	}
	for(int i=2; i<=n; ++i) addEdge(i, i - 1, 0);
}

int solve()
{
	head = tail = 0;
	for(int i=1; i<=n; ++i)
	{
		d[i] = INF;
		in[i] = 0;
		cnt[i] = 0;
	}

	Q[tail++] = 1;
	d[1] = 0;
	in[1] = 1;
	cnt[1] = 1;

	while(head < tail)
	{
		int u = Q[head++];
		for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(d[u] + ptr->len < d[v])
			{
				d[v] = d[u] + ptr->len;
				if(!in[v])
				{
					in[v] = 1;
					Q[tail++] = v;
					cnt[v]++;
					if(cnt[v] > n) return -1;
				}
			}
		}
		in[u] = 0;
	}

	if(d[n] >= 100000000) return -2;
	else return d[n] - d[1];
}

int main()
{
	while(scanf("%d%d%d", &n, &ml, &md) != EOF)
	{
		init();
		printf("%d\n", solve());
	}
	return 0;
}

