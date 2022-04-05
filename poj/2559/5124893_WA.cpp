#include <stdio.h>
#include <cstring>
#define MaxL 100010

struct node
{
	int l, r, mi;
}nd[2][4*MaxL];

int a[2][MaxL], n;
int f[2][MaxL][20];
int lg[MaxL];

int Min(int a, int b){ return (a<b)?a:b; }

void build(int now, int l, int r, int key)
{
	nd[key][now].l = l;
	nd[key][now].r = r;
	if(l < r)
	{
		int mid = (l+r)>>1;
		build(2*now, l, mid, key);
		build(2*now+1, mid+1, r, key);
		nd[key][now].mi = Min(nd[key][2*now].mi, nd[key][2*now+1].mi);
	}
	else nd[key][now].mi = a[key][l];
}

void init()
{
	memset(a, 0, sizeof a);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[0][i]);
		a[1][n+1-i] = a[0][i];
	}
	build(1, 0, n+1, 0);
	build(1, 0, n+1, 1);
	
	for(int k=0; k<2; ++k)
	{
		for(int i=0; i<=n+1; ++i) f[k][i][0] = a[k][i];
		for(int j=1; (1<<j)<=n+2; ++j)
		{
			for(int i=0; i+(1<<j)-1<=n+1; ++i)
			{
				f[k][i][j] = Min(f[k][i][j-1], f[k][i+(1<<(j-1))][j-1]);
			}
		}
	}
	for(int i=1; i<=n+3; ++i)
	{
		lg[i] = 1;
		while((1<<lg[i])<=i) lg[i]++;
		lg[i]--;
	}
}

int getMin(int now, int l, int r, int key)
{
	int len = (r-l+1);
	return Min(f[key][l][lg[len]], f[key][r-(1<<lg[len])+1][lg[len]]);
}

int getIdx(int now, int l, int r, int key, int val)
{
	if(nd[key][now].l==nd[key][now].r) return nd[key][now].l;
	int mid = (nd[key][now].l + nd[key][now].r) >> 1;
	if(r>mid && getMin(1, mid+1, Min(r, nd[key][now].r), key)<val)
		return getIdx(2*now+1, l, r, key, val);
	else return getIdx(2*now, l, r, key, val);
}

void solve()
{
	int ans = -100;
	for(int i=1; i<=n; ++i)
	{
		int lv = i - getIdx(1, 0, i, 0, a[0][i]);
		int rv = n+1-i - getIdx(1, 0, n+1-i, 1, a[0][i]);
		if(a[0][i] * (lv+rv-1) > ans) ans = a[0][i] * (lv+rv-1);
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		init();
		solve();
	}
	return 0;
}