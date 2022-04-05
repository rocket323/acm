#include <stdio.h>
#include <cstring>
#define maxl 100010

struct node
{
	int l, r, sum;
	int suf_min, pre_min, sum_min;
	int suf_max, pre_max, sum_max;
}nd[maxl * 4];

int n, m, a[maxl];

int min(int a, int b){ return (a<b)?a:b; }
int max(int a, int b){ return (a>b)?a:b; }

void update(int now)
{
	int l = 2 * now, r = 2 * now + 1;
	nd[now].sum = nd[l].sum + nd[r].sum;
	
	nd[now].pre_min = min(nd[l].pre_min, nd[l].sum + nd[r].pre_min);
	nd[now].suf_min = min(nd[r].suf_min, nd[r].sum + nd[l].suf_min);
	nd[now].sum_min = min(nd[l].sum_min, min(nd[r].sum_min, nd[l].suf_min + nd[r].pre_min));

	nd[now].pre_max = max(nd[l].pre_max, nd[l].sum + nd[r].pre_max);
	nd[now].suf_max = max(nd[r].suf_max, nd[r].sum + nd[l].suf_max);
	nd[now].sum_max = max(nd[l].sum_max, max(nd[r].sum_max, nd[l].suf_max + nd[r].pre_max));
}

void build(int now, int l, int r)
{
	nd[now].l = l, nd[now].r = r;
	if(l == r)
	{
		nd[now].sum = nd[now].suf_min = nd[now].pre_min = nd[now].sum_min = a[l];
		nd[now].suf_max = nd[now].pre_max = nd[now].sum_max = a[l];
	}
	else
	{
		int mid = (l + r) / 2;
		build(now*2, l, mid);
		build(now*2 + 1, mid + 1, r);
		update(now);
	}
}

void change(int now, int l, int r, int num)
{
	if(l <= nd[now].l && nd[now].r <= r)
	{
		nd[now].sum = nd[now].suf_min = nd[now].pre_min = nd[now].sum_min = num;
		nd[now].suf_max = nd[now].pre_max = nd[now].sum_max = num;
		return;
	}
	int mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) change(now*2, l, r, num);
	if(r > mid) change(now*2+1, l, r, num);

	update(now);
}

void solve()
{
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	build(1, 1, n);

	scanf("%d", &m);
	for(int i=0; i<m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		change(1, a, a, b);

		int sum = nd[1].sum, ans;
		int a1 = nd[1].sum_max;
		int a2 = nd[1].sum_min;

		//printf("%d ", sum);

		if(a1 == sum) printf("%d\n", sum - a2);
		else if(a2 == sum) printf("%d\n", sum - a1);
		else printf("%d\n", max(a1, sum-a2));
	}
}

int main()
{
	scanf("%d", &n);
	solve();
	return 0;
}

