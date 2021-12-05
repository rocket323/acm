#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxl 30010

struct Query
{
	int l, r, k, idx, ans;
} q[200010];

struct Arr
{
	int v, p;
} a[maxl];

struct Node
{
	int l, r, sum;
} nd[maxl * 4];

int n, m, c[maxl];

bool cmp_by_v(const Arr &a, const Arr &b)
{
	return a.v < b.v;
}

bool cmp_by_k(const Query &a, const Query &b)
{
	return a.k < b.k;
}

bool cmp_by_idx(const Query &a, const Query &b)
{
	return a.idx < b.idx;
}

void build(int now, int l, int r)
{
	nd[now].l = l, nd[now].r = r;
	nd[now].sum = 0;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(now * 2, l, mid);
		build(now * 2 + 1, mid + 1, r);
	}
}

void add(int now, int l, int r, int val)
{
	if (l <= nd[now].l && nd[now].r <= r)
	{
		nd[now].sum += val;
		return;
	}
	int mid = (nd[now].l + nd[now].r) >> 1;
	if (l <= mid) add(now * 2, l, r, val);
	if (r > mid) add(now * 2 + 1, l, r, val);

	nd[now].sum = nd[now * 2].sum + nd[now * 2 + 1].sum;
}

int query(int now, int l, int r)
{
	if (l <= nd[now].l && nd[now].r <= r) return nd[now].sum;

	int mid = (nd[now].l + nd[now].r) >> 1, lv = 0, rv = 0;
	if (l <= mid) lv = query(now * 2, l, r);
	if (r > mid) rv = query(now * 2 + 1, l, r);
	return lv + rv;
}

int lowbit(int x) { return x & -x; }

void add(int p, int v)
{
	p += 2;
	while (p < maxl) { c[p] += v; p += lowbit(p); }
}

int query(int p)
{
	int ans = 0;
	p +=2;
	while(p > 0)
	{
		ans += c[p];
		p -= lowbit(p);
	}
	return ans;
}

int main()
{
	//while(scanf("%d", &n) != EOF)
	scanf("%d", &n);
	{
		for (int i = 1; i <= n; ++i)
		{
			a[i].p = i;
			scanf("%d", &a[i].v);
		}
		// build(1, 1, n);
		sort(a + 1, a + 1 + n, cmp_by_v);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
			q[i].idx = i;
		}
		sort(q, q + m, cmp_by_k);

		int l = 1, r = 1;

		memset(c, 0, sizeof c);
		for (int i = 1; i <= n; ++i) add(a[i].p, 1);

		for (int i = 0; i < m; ++i)
		{
			int k = q[i].k;
			while (l <= n && a[l].v <= k) { add(a[l].p, -1); l++; }
			// q[i].ans = query(1, q[i].l, q[i].r);
			q[i].ans = query(q[i].r) - query(q[i].l - 1);
		}

		sort(q, q + m, cmp_by_idx);
		for (int i = 0; i < m; ++i) printf("%d\n", q[i].ans);
	}

	return 0;
}

