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

void dfs1(int now)
{
	l[now][0] = 0; l[now][1] = -INF;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		dfs1(k);
		if(l[k][0] + ptr->len >= l[now][0])
		{
			l[now][1] = l[now][0]; id[now][1] = id[now][0];
			l[now][0] = l[k][0] + ptr->len; id[now][0] = k;
		}
		else if(l[k][0] + ptr->len > l[now][1])
		{
			l[now][1] = l[k][0] + ptr->len; id[now][1] = k;
		}
	}
}

void dfs2(int now)
{
	if(p[now] != -1)
	{
		if(id[p[now]][0] != now) u[now] = l[p[now]][0] + pl[now];
		else u[now] = l[p[now]][1] + pl[now];
	}
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next) dfs2(ptr->idx);
}

struct node
{
	int pos, val;
}
st[maxl];
int top;

/*
void calc(int a[], int left[])
{
	top = 0;
	st[0].pos = 1; st[0].val = a[1];
	left[1] = 1;

	for(int i=2; i<=n; ++i)
	{
		if(!top || a[i] < st[top-1].val)
		{

		}
	}
}
*/

void solve()
{
	dfs1(1);
	memset(u, 0, sizeof u);

	dfs2(1);

	for(int i=1; i<=n; ++i) a[i] = l[i][0] + u[i];

	h1 = h2 = t1 = t2 = 0;
	int ans = 1;
	for(int i=1; i<=n; ++i)
	{
		while(h1 < t1 && a[l1[t1-1]] > a[i]) t1--;
		while(h2 < t2 && a[l2[t2-1]] < a[i]) t2--;
		l1[t1++] = i;
		l2[t2++] = i;

		while(a[l2[h2]] - a[l1[h1]] > m)
		{
			if(l1[h1] < l2[h2]) h1++;
			else h2++;
		}

		ans = max(ans, max(i - l1[h1] + 1, i - l2[h2] + 1));
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

