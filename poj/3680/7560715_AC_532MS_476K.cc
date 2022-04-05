/*
 * =======================================================
 *       Filename:  3680.cpp
 *    Description:  MCMF
 *        Created:  02/09/10 09:42:44
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 500
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, f, w;
	Edge *next, *opp;
}
adj[maxl], memo[maxl * 10];

Edge *pre[maxl];
int mset;
int n, k, l[maxl], r[maxl], w[maxl], b[maxl], top;
int dist[maxl], in[maxl], Q[maxl * 20], head, tail, s, t;

void addEdgeProcess(int a, int b, int c, int w)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->f = c; ptr->w = w;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void addEdge(int a, int b, int c, int w)
{
	addEdgeProcess(a, b, c, w);
	addEdgeProcess(b, a, 0, -w);

	adj[a].next->opp = &memo[mset - 1];
	adj[b].next->opp = &memo[mset - 2];
}

void init()
{
	scanf("%d%d", &n, &k);
	top = 0;
	for(int i=0; i<n; ++i)
	{
		scanf("%d%d%d", &l[i], &r[i], &w[i]);
		b[top++] = l[i];
		b[top++] = r[i];
	}
	sort(b, b + top);
	top = unique(b, b + top) - b;
}

bool spfa(int s, int t)
{
	for(int i=s; i<=t; ++i) dist[i] = INF, in[i] = 0;
	in[s] = 1; dist[s] = 0;

	head = tail = 0;
	Q[tail++] = s;

	while(head < tail)
	{
		int u = Q[head++];
		in[u] = 0;
		for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(ptr->f <= 0) continue;
			if(dist[u] + ptr->w < dist[v])
			{
				dist[v] = dist[u] + ptr->w;
				pre[v] = ptr;
				if(!in[v]) in[v] = 1, Q[tail++] = v;
			}
		}
	}
	return dist[t] < INF;
}

void solve()
{
	s = 0, t = top + 1;
	mset = 0;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;

	for(int i=0; i<top-1; ++i) addEdge(i + 1, i + 2, k, 0);
	addEdge(s, 1, k, 0);
	addEdge(top, t, k, 0);
	for(int i=0; i<n; ++i)
	{
		int x = lower_bound(b, b + top, l[i]) - b;
		int y = lower_bound(b, b + top, r[i]) - b;
		addEdge(x + 1, y + 1, 1, -w[i]);
	}

	int ans = 0;
	while(spfa(s, t))
	{
		int k = t, d = INF;
		while(k != s)
		{
			d = min(d, pre[k]->f);
			k = pre[k]->opp->idx;
		}

		if(dist[t] >= 0) break;

		k = t;
		while(k != s)
		{
			pre[k]->f -= d;
			pre[k]->opp->f += d;
			k = pre[k]->opp->idx;
		}

		ans += dist[t] * d;
	}

	printf("%d\n", -ans);
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

