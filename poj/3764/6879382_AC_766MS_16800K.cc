#include <stdio.h>
#include <cstring>
#define maxl 100010

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[maxl * 2];

struct node
{
	node *next[2];
};

node *root, memo_2[maxl * 40];

int n, mset, mt, p[maxl], d[maxl];

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void dfs(int now, int num)
{
	d[now] = num;

	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] == k) continue;
		p[k] = now;

		dfs(k, num ^ ptr->len);
	}
}

node* newNode()
{
	node *ptr = &memo_2[mt++];
	ptr->next[0] = ptr->next[1] = NULL;
	return ptr;
}

void add(int num)
{
	node * now = root;
	for(int mask=(1<<30); mask>0; mask>>=1)
	{
		int k = (num & mask) > 0;
		if(now->next[k] == NULL) now->next[k] = newNode();
		now = now->next[k];
	}
}

void init()
{
	mset = 0;
	for(int i=0; i<n; ++i) adj[i].next = NULL;

	for(int i=0; i<n-1; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void solve()
{
	memset(p, -1, sizeof p);
	memset(d, 0, sizeof d);
	dfs(0, 0);

	mt = 0;
	root = newNode();
	for(int i=0; i<n; ++i)
	{
		add(d[i]);
	}

	int ans = 0;
	for(int i=0; i<n; ++i)
	{
		int k = ~d[i], tmp = 0;
		node * now = root;
		for(int mask=(1<<30); mask; mask>>=1)
		{
			int v = (k & mask) > 0;
			if(now->next[v])
			{
				now = now->next[v];
				tmp |= mask;
			}
			else now = now->next[v^1];
		}
		if(tmp > ans) ans = tmp;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

