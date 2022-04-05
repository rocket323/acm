/*
 * =======================================================
 *       Filename:  3594.cpp
 *    Description:  
 *        Created:  27/10/10 23:29:24
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define maxl 400
#define INF 0x3f3f3f3f
using namespace std;

struct Edge
{
	int idx, a, b, l;
	Edge *next;
}
adj[maxl], memo[maxl * 200];

struct node
{
	int idx, t;
	node(){}
	node(int _idx, int _t) : idx(_idx), t(_t) {}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.t > B.t;
	}
};

int n, m, d[maxl], ans, mt, s, t, mset;

priority_queue<node, vector<node>, cmp> pq;

void addEdge(int a, int b, int c, int d, int l)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->a = c; ptr->b = d;
	ptr->l = l;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;

	mt = 0;
	for(int i=0; i<m; ++i)
	{
		int a, b, c, d, l;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &l);
		if(a == s && c > mt) mt = c;
		addEdge(a, b, c, d, l);
	}
}

int calc(int st)
{
	while(!pq.empty()) pq.pop();
	for(int i=1; i<=n; ++i) d[i] = INF;
	d[s] = st;
	pq.push(node(s, st));

	int flag = 1;
	if(st == 0) flag = 1;

	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();
		if(now.t > d[now.idx]) continue;

		if(now.idx == t) return now.t;

		for(Edge *ptr=adj[now.idx].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			int st = (now.t < ptr->a) ? ptr->a : now.t;
			if(st + ptr->l > ptr->b) continue;
			if(st + ptr->l < d[v])
			{
				d[v] = st + ptr->l;
				pq.push(node(v, d[v]));
			}
		}
	}
	/*
	if(flag)
	{
		for(int i=1; i<=n; ++i) printf("%d ", d[i]);
		puts("");
	}
	*/
	return INF + 10000000;
}

void solve()
{
	ans = INF;
	for(int i=0; i<=mt; ++i)
	{
		int k = calc(i) - i;
		if(k < ans) ans = k;
	}
	if(ans >= INF) puts("Impossible");
	else printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d%d%d", &n, &m, &s, &t) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

