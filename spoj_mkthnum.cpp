#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxl 100010

int n, m, a[maxl], p[maxl];
int l, r, k, rk[maxl], root[maxl];
int mset;

struct node
{
	int lp, rp, sum;
}nd[maxl * 20];

bool cmp(int i, int j)
{
	return a[i] < a[j];
}

int build(int l, int r)
{
	int rt= mset++;
	nd[rt].sum = 0;

	if (l < r)
	{
		int mid = (l + r) >> 1;
		nd[rt].lp = build(l, mid);
		nd[rt].rp = build(mid + 1, r);
	}
	return rt;
}

int add(int l, int r, int p, int v, int ta)
{
	int rt = mset++;
	nd[rt] = nd[ta];
	nd[rt].sum += v;
	if (l == r) return rt;

	int mid = (l + r) >> 1;
	if (p <= mid) nd[rt].lp = add(l, mid, p, v, nd[ta].lp);
	else nd[rt].rp = add(mid + 1, r, p, v, nd[ta].rp);
	return rt;
}

int query(int l, int r, int ta, int tb, int k)
{
	if (l == r) return l;
	int mid = (l + r) >> 1;
	int x = nd[nd[ta].lp].sum - nd[nd[tb].lp].sum;
	if (x >= k)
		return query(l, mid, nd[ta].lp, nd[tb].lp, k);
	else
		return query(mid + 1, r, nd[ta].rp, nd[tb].rp, k - x);
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		mset = 0;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &a[i]);
			p[i] = i;
		}
		sort(p + 1, p + 1 + n, cmp);
		for (int i = 1; i <= n; ++i) rk[p[i]] = i;

		root[0] = build(1, n);
		for (int i = 1; i <= n; ++i) root[i] = add(1, n, rk[i], 1, root[i - 1]);

		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", &l, &r, &k);
			int ans = query(1, n, root[r], root[l - 1], k);
			printf("%d\n", a[p[ans]]);
		}
	}
}

