#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 40010

int t, n;
int l[maxl], r[maxl], b[maxl * 2], top;

struct node
{
	int l, r, sum, flag;
} nd[maxl * 4];

int getPos(int x) { return lower_bound(b, b + top, x) - b + 1; }

void build(int now, int l, int r)
{
	nd[now].l = l; nd[now].r = r;
	nd[now].sum = nd[now].flag = 0;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(now * 2, l, mid);
		build(now * 2 + 1, mid + 1, r);
	}
}

void pushDown(int now)
{
	if (nd[now].flag == 0) return;
	nd[now * 2].flag = nd[now * 2 + 1].flag = 1;
	nd[now * 2].sum = (nd[now*2].r - nd[now*2].l + 1);
	nd[now * 2 + 1].sum = (nd[now*2+1].r - nd[now*2+1].l + 1);
	nd[now].flag = 0;
}

void add(int now, int l, int r)
{
	if (l <= nd[now].l && nd[now].r <= r)
	{
		nd[now].sum = (nd[now].r - nd[now].l + 1);
		nd[now].flag = 1;
		return;
	}
	if (nd[now].flag) return;
	
	int mid = (nd[now].l + nd[now].r) >> 1;
	if (l <= mid) add(now * 2, l, r);
	if (r > mid) add(now * 2 + 1, l, r);

	// update
	nd[now].sum = nd[now * 2].sum + nd[now * 2 + 1].sum;
}

int query(int now, int l, int r)
{
	pushDown(now);
	if (l <= nd[now].l && nd[now].r <= r)
	{
		return nd[now].sum;
	}
	int mid = (nd[now].l + nd[now].r) >> 1, lv = 0, rv = 0;
	if (l <= mid) lv = query(now * 2, l, r);
	if (r > mid) rv = query(now * 2 + 1, l, r);
	return lv + rv;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		top = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d%d", &l[i], &r[i]);
			b[top++] = l[i]; b[top++] = r[i];
		}
		sort(b, b + top);
		top = unique(b, b + top) - b;

		build(1, 1, top);
		int ans = 0;
		for (int i = n; i >= 1; --i)
		{
			int la = getPos(l[i]), lb = getPos(r[i]);
			int width = query(1, la, lb);
			if (width < lb - la + 1) ans++;

			add(1, la, lb);
		}
		printf("%d\n", ans);
	}

	return 0;
}

