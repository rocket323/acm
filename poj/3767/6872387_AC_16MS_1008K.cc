#include <stdio.h>
#include <cstring>
#define maxl 1500
#define maxe 1000010
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct node
{
	int idx, len;
	node(int _idx, int _len): idx(_idx), len(_len){}
};

struct cmp
{
	bool operator()(node A, node B)
	{
		return A.len > B.len;
	}
};

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[maxe];

priority_queue<node, vector<node>, cmp> pq;
int n, m, a[maxe], b[maxe], c[maxe], d[maxl], v[maxl];
int mset;

void addEdge(int a, int b, int c)
{
	Edge * ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=2*n; ++i) adj[i].next = NULL;

	for(int i=0; i<m; ++i)
	{
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	}

	for(int i=1; i<=n; ++i) scanf("%d", &v[i]);

	for(int i=0; i<m; ++i)
	{

		if(v[a[i]] != v[b[i]])
		{
			addEdge(a[i], b[i] + n, c[i]);
			addEdge(b[i], a[i] + n, c[i]);
		}
		else
		{
			addEdge(a[i], b[i], c[i]);
			addEdge(b[i], a[i], c[i]);
			addEdge(a[i] + n, b[i] + n, c[i]);
			addEdge(b[i] + n, a[i] + n, c[i]);
		}
	}
}

void dijstra()
{
	memset(d, 0x3f, sizeof d);
	d[1] = 0;

	while(!pq.empty()) pq.pop();
	pq.push(node(1, 0));

	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();
		if(now.len > d[now.idx]) continue;

		int k = now.idx;
		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(d[k] + ptr->len < d[v])
			{
				d[v] = d[k] + ptr->len;
				pq.push(node(v, d[v]));
			}
		}
	}
}

void solve()
{
	dijstra();
	int k = min(d[2], d[2+n]);

	if(k >= 0x3f3f3f3f) puts("-1");
	else printf("%d\n", k);
}

int main()
{
	while(scanf("%d", &n), n)
	{
		scanf("%d", &m);
		init();
		solve();
	}
	return 0;
}

