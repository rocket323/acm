#include <stdio.h>
#define MaxL 100010
#define ll long long
#define INF 10000000000000LL
#define MM 10000000

struct node
{
	int l, r;
	int mx;
}nd[4*MaxL];

int n, a[MaxL];
long long m, s[MaxL], f[MaxL];

int Max(int a, int b){ return (a>b)?a:b; }

void build(int now, int l, int r)
{
	nd[now].l = l; nd[now].r = r;
	if(l<r)
	{
		int mid = (l+r)>>1;
		build(2*now, l, mid);
		build(2*now+1, mid+1, r);
		nd[now].mx = Max(nd[2*now].mx, nd[2*now+1].mx);
	}
	else nd[now].mx = a[l];
}

void init()
{
	s[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		s[i] = (ll)s[i-1] + a[i];
	}
	build(1, 1, n);
}

ll Min(ll a, ll b){ return (a<b)?a:b; }

int getMax(int now, int l, int r)
{
	if(l<=nd[now].l && nd[now].r<=r) return nd[now].mx;
	int lv = -1, rv = -1;
	int mid = (nd[now].l + nd[now].r) >> 1;
	if(l<=mid) lv = getMax(2*now, l, r);
	if(r>mid) rv = getMax(2*now+1, l, r);
	return Max(lv, rv);
}

void solve()
{
	f[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		f[i] = INF;
		for(int j=i-1; j>=0; --j)
		{
			if(s[i] - s[j] > m) break;
			f[i] = Min(f[i], f[j] + getMax(1, j+1, i));
		}
	}
	if(f[n]==INF) printf("-1\n");
	else printf("%I64d\n", f[n]);
}

int main()
{
	while(scanf("%d%I64d", &n, &m)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
