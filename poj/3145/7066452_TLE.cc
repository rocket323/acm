#include <stdio.h>
#include <cstring>
#define maxl 500010
#define MM 500001
#define INF 0x3f3f3f3f

struct node
{
	 int l, r, mn;
}
nd[maxl * 4];

int n, a[800][800], p[maxl], m, t, x;

int min(int a, int b){ return a < b ? a : b; }

void build(int now, int l, int r)
{
	 nd[now].l = l, nd[now].r = r, nd[now].mn = INF;
	 if(l < r)
	 {
		  int mid = (l + r) / 2;
		  build(now * 2, l, mid);
		  build(now * 2 + 1, mid + 1, r);
	 }
}

int get_min(int now, int l, int r)
{
	 if(l <= nd[now].l && nd[now].r <= r) return nd[now].mn;
	 int mid = (nd[now].l + nd[now].r) / 2, lv = INF, rv = INF;
	 if(l <= mid) lv = get_min(now * 2, l, r);
	 if(r > mid) rv = get_min(now * 2 + 1, l, r);
	 return min(lv, rv);
}

void add(int now, int l, int r)
{
	 if(l <= nd[now].l && nd[now].r <= r)
	 {
		  nd[now].mn = l;
		  return;
	 }
	 int mid = (nd[now].l + nd[now].r) / 2;
	 if(l <= mid) add(now * 2, l, r);
	 if(r > mid) add(now * 2 + 1, l, r);

	 nd[now].mn = min(nd[now * 2].mn, nd[now * 2 + 1].mn);
}

void init()
{
	 build(1, 0, 500001);
	 memset(a, -1, sizeof a);
	 memset(p, -1, sizeof p);
}

void solve()
{
	 char str[3];
	 m = 720;
	 t = 0;
	 for(int i=0; i<n; ++i)
	 {
		  scanf("%s%d", str, &x);
		  if(str[0] == 'B')
		  {
			   p[x] = ++t;
			   add(1, x, x);
			   for(int i=1; i<m; ++i) a[i][x%i] = t;
		  }
		  else
		  {
			   int ans = -1;
			   if(x < m)
			   {
					for(int i=0; i<x && !(ans+1); ++i) if(a[x][i] != -1) ans = a[x][i];
					printf("%d\n", ans);
			   }
			   else
			   {
					int ans_n = INF, ans_t = -1, t_n;
					for(int st=0; st<MM; st+=x)
					{
						 int en = st + x;
						 if(en >= MM) en = MM - 1;
						 t_n = get_min(1, st, en);
						 if(t_n == INF) continue;
						 if(t_n % x < ans_n)
						 {
							  ans_n = t_n % x;
							  ans_t = p[t_n];
						 }
						 else if(t_n % x == ans_n && p[t_n] > ans_t)
						 {
							  ans_t = p[t_n];
						 }
					}
					printf("%d\n", ans_t);
			   }
		  }
	 }
}

int main()
{
	 int tc = 0;
	 while(scanf("%d", &n), n)
	 {
		  if(tc) puts("");
		  printf("Case %d:\n", ++tc);
		  init();
		  solve();
	 }
	 return 0;
}
