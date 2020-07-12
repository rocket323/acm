#include <stdio.h>
#include <cstring>
#include <vector>
#define maxl 100010

using namespace std;
int n, a[maxl], d[maxl], mset, ans;
bool vis[maxl];

struct Edge
{
	int v, l;
	Edge *next;
}
adj[maxl], mem[maxl * 2];

void add_edge(int a, int b, int c)
{
	Edge *ed = &mem[mset++];
	ed->v = b;
	ed->l = c;
	ed->next = adj[a].next;
	adj[a].next = ed;
}

void dfs(int u)
{
	vis[u] = 1;
	for (Edge *e = adj[u].next; e; e = e->next)
	{
		int v = e->v, l = e->l;
		d[v] = d[u] + l;
		if (vis[v]) dfs(v);
	}
}

void dfs2(int u, int max_d)
{
	vis[u] = 1;
	for (Edge *e = adj[u].next; e; e = e->next)
	{
		int v = e->v, l = e->l;
		if (vis[v]) continue;
		int dd = max(l, l + max_d);
		if (dd <= a[v])
		{
			ans++;
			dfs2(v, dd);
		}
	}
}

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		mset = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &a[i]);
			adj[i].next = NULL;
		}

		for (int i = 1; i < n; ++i)
		{
			int p, c;
			scanf("%d%d", &p, &c);
			add_edge(i + 1, p, c);
			add_edge(p, i + 1, c);
		}

		d[1] = 0;
		memset(vis, 0, sizeof vis);
		dfs(1);

		memset(vis, 0, sizeof vis);
		ans = 1;
		dfs2(1, 0);
		printf("%d\n", n - ans);
	}

	return 0;
}

