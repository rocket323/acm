#include <stdio.h>
#include <cstring>
#define MaxL 100010
//#define min(a,b) ((a<b)?a:b)
#define INF 1000000000000000LL
#define ll long long

struct node
{
	int l, r;
	ll num, flag;
}nd[MaxL * 4];

struct queue
{
	int h, last;
}Q[MaxL];

int top, n, h[MaxL];
ll s[MaxL], m;
ll f[MaxL];

ll min(ll a, ll b){ return (a<b)?a:b; }

void build(int now, int l, int r)
{
	nd[now].l = l, nd[now].r = r;
	nd[now].num = nd[now].flag = 0;
	if(l < r)
	{
		int mid = (l + r) / 2;
		build(now*2, l, mid);
		build(now*2+1, mid+1, r);
	}
}

void init()
{
	s[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &h[i]);
		s[i] = s[i-1] + h[i];
	}
	build(1, 0, n);
}

void flagDown(int now)
{
	if(nd[now].flag)
	{
		nd[now].num += nd[now].flag;
		if(nd[now].l != nd[now].r) nd[now*2].flag += nd[now].flag;
		if(nd[now].l != nd[now].r) nd[now*2+1].flag += nd[now].flag;
		nd[now].flag = 0;
	}
}

void update(int now)
{
	nd[now].num = min(nd[now*2].num, nd[now*2+1].num);
}

void add(int now, int l, int r, ll val)
{
	flagDown(now);
	if(l<=nd[now].l && nd[now].r<=r)
	{
		nd[now].flag = val;
		flagDown(now);
		return;
	}
	int mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) add(now*2, l, r, val);
	if(r > mid) add(now*2+1, l, r, val);

	update(now);
}

ll getTree(int now, int l, int r)
{
	flagDown(now);
	if(l<=nd[now].l && nd[now].r<=r)
	{
		return nd[now].num;
	}

	ll lv = INF, rv = INF;
	int mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) lv = getTree(now*2, l, r);
	if(r > mid) rv = getTree(now*2+1, l, r);

	return min(lv, rv);
}

void solve()
{

	for(int i=1; i<=n; ++i) if(h[i] > m) { puts("-1"); return; }

	int k = 0;
	Q[top = 0].last = -1;
	Q[top = 1].h = 0, Q[top].last = 0;
	f[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		while(s[i] - s[k] > m) k++;

		while(top && h[i] >= Q[top].h)
		{
			add(1, Q[top-1].last+1, Q[top].last, h[i] - Q[top].h);
			top--;
		}
		Q[++top].h = h[i], Q[top].last = i - 1;
		Q[++top].h = 0, Q[top].last = i;
		f[i] = getTree(1, k, i-1);
/*
		puts("*********");
		for(int j=1; j<=top; ++j)
		{
			printf("%intd ", Q[i].h);
		}
		puts("\n************");

		//printf("%intd %intd\n", i, f[i]);
*/
		add(1, i, i, f[i]);
	}

	printf("%lld\n", f[n]);
}

int main()
{
	while(scanf("%d%lld", &n, &m) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

