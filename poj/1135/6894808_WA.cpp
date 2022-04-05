#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 505
#define maxe 500010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, l, lv;
	Edge *next;
}
adj[maxl], memo[maxe];

int n, m, mset, vis[maxl], a[maxe], b[maxe], c[maxe];
int ans[maxe], d[maxl];

void addEdge(int a, int b, int l, int lv)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->l = l;
	ptr->lv = lv;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=0; i<m; ++i)
	{
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		addEdge(a[i], b[i], 2 * c[i], i);
		addEdge(b[i], a[i], 2 * c[i], i);
	}
}

void solve()
{
	memset(d, 0x3f, sizeof d);
	memset(ans, -1, sizeof ans);
	memset(vis, 0, sizeof vis);

	d[1] = 0;

	while(true)
	{
		int k = -1, len = INF;
		for(int i=1; i<=n; ++i)
		{
			if(!vis[i] && d[i] < len)
			{
				len = d[i];
				k = i;
			}
		}
		if(k == -1) break;

		vis[k] = 1;

		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(!vis[v] && d[k] + ptr->l > d[v])
			{
				ans[ptr->lv] = d[k] + (ptr->l - d[v] + d[k]) / 2;
			}
			if(d[k] + ptr->l < d[v]) d[v] = d[k] + ptr->l;
		}
	}

	int _a = -1, _b = -1, len = 0;
	for(int i=1; i<=n; ++i) if(d[i] > len)
	{
		len = d[i], _b = i;
	}
	for(int i=0; i<m; ++i)
	{
		if(ans[i] > len)
		{
			len = ans[i];
			_a = a[i];
			_b = b[i];
		}
	}

	if(_a > _b) swap(_a, _b);

	if(_a == -1) printf("The last domino falls after %.1lf seconds, at key domino %d.\n", len / 2.0, _b);
	else printf("The last domino falls after %.1lf seconds, between key dominoes %d and %d.\n", len / 2.0, _a, _b);

}

int main()
{
	int tc = 0;
	while(scanf("%d%d", &n, &m), (n + m))
	{
		printf("System #%d\n", ++tc);
		init();
		solve();
		puts("");
	}
	return 0;
}

