//poj1177 picture
//求N个矩形并的周长

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxl 5020
#define min(a,b) ((a<b)?a:b)

struct rect
{
	int x1, y1, x2, y2;
}rt[maxl];

struct node
{
	int l, r;
	int len, cover, buf, sum;
}nd[8 * maxl];

int n, ans, pl[maxl], pu[maxl], sx, sy;
vector<int> Bx(maxl), By(maxl);

bool cmpLow(int x, int y){ return rt[x].y1 < rt[y].y1; }
bool cmpHigh(int x, int y){ return rt[x].y2 < rt[y].y2; }

int getID(int x, vector<int> A, int size)
{
	int low = 0, high = size - 1, mid, ans = -1;

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(A[mid] <= x)
		{
			ans = mid;
			low = mid + 1;
		}
		else high = mid - 1;
	}
	return ans;
}

void init()
{

	Bx.clear();
	By.clear();
	for(int i=0; i<n; ++i)
	{
		Bx.push_back(rt[i].x1); Bx.push_back(rt[i].x2);
		By.push_back(rt[i].y1); By.push_back(rt[i].y2);
	}
	sort(pl, pl+n, cmpLow);
	sort(pu, pu+n, cmpHigh);
	sort(Bx.begin(), Bx.end());
	sort(By.begin(), By.end());

	sx = unique(Bx.begin(), Bx.end()) - Bx.begin();
	sy = unique(By.begin(), By.end()) - By.begin();

	//for(int i=0; i<sx; ++i) printf("%d ", Bx[i]);
	//puts("");
}

void build(int now, int l, int r, vector<int> Bx)
{
	nd[now].l = l; nd[now].r = r;
	nd[now].len = nd[now].sum = Bx[r] - Bx[l-1];
	nd[now].cover = nd[now].buf = 0;

	if(l < r)
	{
		int mid = (l + r) / 2;
		build(now * 2, l, mid, Bx);
		build(now * 2 + 1, mid + 1, r, Bx);
	}
}

void flagDown(int now)
{
	if(!nd[now].buf) return;

	nd[now].cover += nd[now].buf;
	if(nd[now].cover > 0)
	{
		nd[now].sum = Bx[nd[now].r] - Bx[nd[now].l-1];
	}
	else nd[now].sum = nd[now*2].sum + nd[now*2+1].sum;

	if(nd[now].l != nd[now].r)
	{
		int left = now * 2, right = left + 1;
		nd[left].buf += nd[now].buf;
		nd[right].buf += nd[now].buf;
	}
	nd[now].buf = 0;
}

void update(int now)
{
	int left = now * 2, right = left + 1;
	nd[now].sum = (nd[left].cover ? 0 : nd[left].sum) + (nd[right].cover ? 0 : nd[right].sum);
	//nd[now].cover = min(nd[left].cover, nd[right].cover);
}

int query(int now, int l, int r)
{
	if(nd[now].cover > 0) return 0;
	if(l <= nd[now].l && nd[now].r <= r)
	{
		if(nd[now].cover > 0) return 0;
		else return nd[now].sum;
	}

	int lv = 0, rv = 0, mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) lv = query(now * 2, l, r);
	if(r > mid) rv = query(now * 2 + 1, l, r);

	return lv + rv;
}

void change(int now, int l, int r, int num)
{
	if(l <= nd[now].l && nd[now].r <= r)
	{
		nd[now].cover += num;

		if(nd[now].l == nd[now].r)
		{
			if(nd[now].cover > 0) nd[now].sum = 0;
			else nd[now].sum = nd[now].len;
		}
		return;
	}
	int mid = (nd[now].l + nd[now].r) / 2;
	if(l <= mid) change(now * 2, l, r, num);
	if(r > mid) change(now * 2 + 1, l, r, num);
	update(now);
}

int go()
{
	int ans = 0;

	init();
	build(1, 1, sx-1, Bx);

	int low = 0, up = 0;
	for(int i=0; i<sy; ++i)
	{
		while(low < n && rt[pl[low]].y1 <= By[i])
		{
			if(rt[pl[low]].y1 == By[i])
			{
				int left = getID(rt[pl[low]].x1, Bx, sx) + 1, right = getID(rt[pl[low]].x2, Bx, sx);
				int tmp = query(1, left, right);
				ans += tmp;
				//puts("\n****************************");
				//for(int i=1; i<=5; ++i) printf("%d ", nd[i].cover);
				//puts("");

				change(1, left, right, 1);

				//for(int i=1; i<=5; ++i) printf("%d ", nd[i].cover);
				//puts("");
				//printf("low %d %d %d %d %d %d %d\n", By[i], rt[pl[low]].x1, rt[pl[low]].x2, left, right, pl[low], tmp);
				//puts("\n****************************");
			}
			low++;
		}

		while(up < n && rt[pu[up]].y2 <= By[i])
		{
			if(rt[pu[up]].y2 == By[i])
			{
				int left = getID(rt[pu[up]].x1, Bx, sx) + 1, right = getID(rt[pu[up]].x2, Bx, sx);

				/*
				puts("\n************************************************");
				for(int i=1; i<=5; ++i) printf("%d ", nd[i].cover);
				puts("");
				*/
				change(1, left, right, -1);


				//for(int i=1; i<=5; ++i) printf("%d ", nd[i].cover);
				//puts("");

				int tmp = query(1, left, right);
				//printf("up %d %d %d %d %d %d %d\n", By[i], rt[pu[up]].x1, rt[pu[up]].x2, left, right, pu[up], tmp);
				ans += tmp;
				//puts("\n************************************************");
			}
			up++;
		}
	}

	return ans;
}

void swap(int* a, int* b)
{
	int tmp;
	tmp = *a; *a = *b; *b = tmp;
}

void solve()
{
	for(int i=0; i<n; ++i)
	{
		scanf("%d%d%d%d", &rt[i].x1, &rt[i].y1, &rt[i].x2, &rt[i].y2);
		pl[i] = pu[i] = i;
	}

	int k1 = go();

	for(int i=0; i<n; ++i)
	{
		int tmp;
		swap(&rt[i].x1, &rt[i].y1);
		swap(&rt[i].x2, &rt[i].y2);
	}

	//int k2 = 0;
	int k2 = go();

	ans = k1 + k2;
	//printf("%d %d %d\n", k1, k2, ans);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		solve();
	}
	return 0;
}

