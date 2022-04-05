#include <stdio.h>
#include <cstring>
#include <queue>
using namespace std;
#define MaxL 501
#define UNVIS 0
#define VIS 1
#define OVER 2
#define INF 0x7f7f7f7f

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[2][MaxL], memo[2*MaxL*MaxL];

struct node
{
	int id, dist;
	node(int a, int b):id(a), dist(b){}
};

struct cmp
{
	bool operator()(node A, node B){ return A.dist > B.dist; }
};

priority_queue<node, vector<node>, cmp> pq;
int S[MaxL], id[MaxL], low[MaxL], mark[MaxL], pre[MaxL], lv, sz;
int d[MaxL], n, m, mset;

void addEdge(int key, int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[key][a].next;
	adj[key][a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[0][i].next = adj[1][i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(0, a, b, c);
	}
}

void dfs(int now)
{
	id[now] = low[now] = lv++;
	mark[now] = VIS;
	S[++sz] = now;
	Edge *ptr = adj[0][now].next;
	while(ptr)
	{
		int k = ptr->idx;
		if(mark[k]==UNVIS)
		{
			dfs(k);
			if(low[k]<low[now]) low[now] = low[k];
		}
		else if(mark[k]==VIS)
		{
			if(low[k]<low[now]) low[now] = low[k];
		}
		ptr = ptr->next;
	}
	if(id[now]==low[now])
	{
		do
		{
			pre[S[sz]] = now;
			mark[S[sz]] = OVER;
		}while(S[sz--]!=now);
	}
}

void tarjan()
{
	memset(mark, 0, sizeof mark);
	lv = sz = 0;
	for(int i=1; i<=n; ++i)
	{
		if(mark[i]==UNVIS) dfs(i);
	}
}

void make_Gra()
{
	for(int i=1; i<=n; ++i)
	{
		Edge *ptr = adj[0][i].next;
		while(ptr)
		{
			if(pre[ptr->idx]!=pre[i])
			{
				addEdge(1, pre[i], pre[ptr->idx], ptr->len);
			}
			ptr = ptr->next;
		}
	}
}

int dijkstra(int s, int t)
{
	memset(d, 0x7f, sizeof d);
	d[s] = 0;
	while(!pq.empty()) pq.pop();
	pq.push(node(s, 0));

	while(!pq.empty())
	{
		node now = pq.top();
		pq.pop();
		if(now.dist > d[now.id]) continue;
		if(now.id==t) return now.dist;
		for(Edge *ptr=adj[1][now.id].next; ptr; ptr=ptr->next)
		{
			if(now.dist + ptr->len < d[ptr->idx])
			{
				d[ptr->idx] = now.dist + ptr->len;
				pq.push(node(ptr->idx, d[ptr->idx]));
			}
		}
	}
	return INF;
}

void solve()
{
	tarjan();
	make_Gra();
	int q;
	scanf("%d", &q);
	for(int i=0; i<q; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		int k = dijkstra(pre[a], pre[b]);
		if(k>=INF) printf("Nao e possivel entregar a carta\n");
		else printf("%d\n", k);
	}
}

int main()
{
	while(scanf("%d%d", &n, &m) && n)
	{
		init();
		solve();
		printf("\n");
	}
	return 0;
}