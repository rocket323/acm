#include <stdio.h>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MaxL 30010
#include <iostream>
using namespace std;

struct Edge
{
	int idx, w;
	Edge *next;
}
adj[MaxL], memo[6*MaxL];

struct node
{
	int idx, dist;
	node(int i, int j): idx(i), dist(j){}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.dist > B.dist;
	}
};

int n, m, d[MaxL], mset;
priority_queue<node, vector<node>, cmp> pq;

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->w = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
	}
}

void solve()
{
	memset(d, 0x3f, sizeof d);
	d[1] = 0;
	while(!pq.empty()) pq.pop();
	pq.push(node(1, 0));
	
	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();
		if(now.dist > d[now.idx]) continue;
		
		for(Edge *ptr=adj[now.idx].next; ptr; ptr=ptr->next)
		{
			if(now.dist + ptr->w < d[ptr->idx])
			{
				d[ptr->idx] = now.dist + ptr->w;
				pq.push(node(ptr->idx, d[ptr->idx]));
			}
		}
	}
	printf("%d\n", d[n]);
}

int main()
{
	scanf("%d%d", &n, &m);
	init();
	solve();
	return 0;
}
