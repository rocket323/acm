#include <stdio.h>
#include <cstring>
#define maxl 500010
#define LC ((now) * 2)
#define RC ((now) * 2 + 1)

struct node
{
	int l, r, cnt;
}
nd[maxl * 4];

int f[maxl], a[maxl], fac[maxl];
int vis[maxl + 10], list[maxl], top, n, m;
char name[maxl][20];
int out[maxl], can[maxl];

void build(int now, int l, int r)
{
	nd[now].l = l, nd[now].r = r;
	if(l == r) nd[now].cnt = 1;
	else
	{
		int mid = (l + r) / 2;
		build(now * 2, l, mid);
		build(now * 2 + 1, mid + 1, r);
		nd[now].cnt = nd[LC].cnt + nd[RC].cnt;
	}
}

int get_cnt(int now, int l, int r)
{
	if(l <= nd[now].l && nd[now].r <= r) return nd[now].cnt;
	int mid = (nd[now].l + nd[now].r) / 2, lv = 0, rv = 0;
	if(l <= mid) lv = get_cnt(LC, l, r);
	if(r > mid) rv = get_cnt(RC, l, r);
	return lv + rv;
}

void dec(int now, int l, int r)
{
	if(l <= nd[now].l && nd[now].r <= r)
	{
		nd[now].cnt--;
		return;
	}
	int mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) dec(now * 2, l, r);
	if(r > mid) dec(now * 2 + 1, l, r);

	nd[now].cnt = nd[LC].cnt + nd[RC].cnt;
}

int get_idx(int now, int l, int r, int pos)
{
	if(nd[now].l == nd[now].r) return nd[now].l;
	int mid = (nd[now].l + nd[now].r) / 2;
	int k = nd[LC].cnt;
	if(k >= pos) return get_idx(LC, l, r, pos);
	else return get_idx(RC, l, r, pos - k);
}

int check(int n)
{
	int ans = 0;
	for(int i=1; i<=n; ++i) if(n % i == 0) ans++;
	return ans;
}

int main()
{

	top = 0;
	memset(vis, 0, sizeof vis);
	memset(fac, -1, sizeof fac);
	for(int i=2; i<maxl; ++i)
	{
		if(vis[i]) continue;
		for(int j=i+i; j<maxl; j+=i)
		{
			if(fac[j] == -1) fac[j] = i;
			vis[j] = 1;
		}
	}

	f[1] = 1;
	f[2] = 2;
	for(int i=3; i<maxl; ++i)
	{
		if(!vis[i]) f[i] = 2;
		else
		{
			int cnt = 0, num = i, p = 1, x = fac[i];
			while(num % x == 0){ p *= x; cnt++; num /= x; }

			f[i] = (cnt + 1) * f[i / p];

		}
	}
	
	//printf("%d %d\n", f[5000], check(5000));

	while(scanf("%d%d", &n, &m) != EOF)
	{
		build(1, 1, n);
		for(int i=1; i<=n; ++i)
		{
			scanf("%s%d", name[i], &a[i]);
		}

		//for(int i=1; i<=n; ++i) printf("%d ", f[i]);
		//puts("");

		memset(out, -1, sizeof out);
		int p = m, left = n;
		for(int i=1; i<=n; ++i)
		{
			left--;
			out[p] = i;
			can[p] = f[i];

			//printf("%d %d\n", i, p);

			dec(1, p, p);

			if(left == 0) break;

			int cnt;
			if(a[p] > 0)
			{
				if(p == n) cnt = 0;
				else cnt = get_cnt(1, p + 1, n);

				if(cnt >= a[p]) p = get_idx(1, p + 1, n, a[p]);
				else
				{
					int t = (a[p] - cnt - 1) % left + 1;
					p = get_idx(1, 1, n, t);
				}
			}
			else
			{
				if(p == 1) cnt = 0;
				else cnt = get_cnt(1, 1, p - 1);


				if(cnt >= -a[p]) p = get_idx(1, 1, p - 1, cnt + 1 + a[p]);
				else
				{
					int num = -a[p];
					int t = (num - cnt - 1) % left + 1;
					t = (left + 1 - t);
					//if(p == 6) printf("n %d %d %d %d\n", cnt, left, num, t);
					p = get_idx(1, 1, n, t);
				}
			}
		}

		int idx = 1, cnt = can[1], t = out[1];
		for(int i=1; i<=n; ++i)
		{
			if(can[i] > can[idx] || (can[i] == can[idx] && out[i] < out[idx])) idx = i;
		}

		printf("%s %d\n", name[idx], can[idx]);
	}
	return 0;
}

