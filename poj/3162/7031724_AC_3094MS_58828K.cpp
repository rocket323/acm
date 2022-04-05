#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1000010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[maxl];

int n, m, l[maxl][2], id[maxl][2];
int mset, p[maxl], a[maxl], u[maxl], pl[maxl];
int left[maxl], right[maxl], root, d[maxl];
int l1[maxl], l2[maxl], h1, h2, t1, t2;

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;

	memset(p, -1, sizeof p);
	pl[1] = 0;
	for(int i=2; i<=n; ++i)
	{
		int a, l;
		scanf("%d%d", &a, &l);
		addEdge(a, i, l);
		p[i] = a; pl[i] = l;
	}
}

void update(int now, int val, int lik)
{
	if(val > l[now][0])
	{
		l[now][1] = l[now][0]; id[now][1] = id[now][0];
		l[now][0] = val; id[now][0] = lik;
	}
	else if(val > l[now][1])
	{
		l[now][1] = val; id[now][1] = lik;
	}
}

void dfs1(int now)
{
	l[now][0] = 0; l[now][1] = -INF;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		dfs1(k);
		update(now, l[k][0] + ptr->len, k);
	}
}

void dfs2(int now)
{
	if(p[now] != -1)
	{
		if(id[p[now]][0] != now)
			update(now, l[p[now]][0] + pl[now], p[now]);
		else
			update(now, l[p[now]][1] + pl[now], p[now]);
	}
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next) dfs2(ptr->idx);
}

void out(int l[], int s, int t)
{
	for(int i=s; i<t; ++i) printf("%d ", l[i]);
	puts("");
}

void solve()
{
	dfs1(1);
	memset(u, 0, sizeof u);
	dfs2(1);
	for(int i=1; i<=n; ++i) a[i] = l[i][0];

	h1 = h2 = t1 = t2 = 0;
	int ans = 1, p = 1;
	for(int i=1; i<=n; ++i)
	{
		while(h1 < t1 && a[l1[t1-1]] >= a[i]) t1--;
		while(h2 < t2 && a[l2[t2-1]] <= a[i]) t2--;
		l1[t1++] = i;
		l2[t2++] = i;

		while(a[l2[h2]] - a[l1[h1]] > m)
		{
			p++;
			while(h1 < t1 && l1[h1] < p) h1++;
			while(h2 < t2 && l2[h2] < p) h2++;
		}

		ans = max(ans, i - p + 1);
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

