//poj1177 picture
//求N个矩形并的周长

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxl 5020
#define min(a,b) ((a<b)?a:b)
#define LEN(now) (Bx[nd[(now)].r] - Bx[nd[(now)].l-1])

struct rect
{
	int x1, y1, x2, y2;
}rt[maxl];

struct node
{
	int l, r;
	int cover, sum;
}nd[8 * maxl];

int n, ans, pl[maxl], pu[maxl], sx, sy;
vector<int> Bx(maxl), By(maxl);

bool cmpLow(int x, int y){ return rt[x].y1 < rt[y].y1; }
bool cmpHigh(int x, int y){ return rt[x].y2 < rt[y].y2; }

int getID(int x, int size)
{
	int low = 0, high = size - 1, mid, ans = -1;

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(Bx[mid] <= x)
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
}

void build(int now, int l, int r)
{
	nd[now].l = l; nd[now].r = r;
	nd[now].sum = 0;
	nd[now].cover = 0;

	if(l < r)
	{
		int mid = (l + r) / 2;
		build(now * 2, l, mid);
		build(now * 2 + 1, mid + 1, r);
	}
}

void update(int now)
{
	int left = now * 2, right = left + 1;
	nd[now].sum = (nd[left].cover ? LEN(left) : nd[left].sum) + (nd[right].cover ? LEN(right) : nd[right].sum);
}

int query(int now, int l, int r)
{
	if(nd[now].cover > 0) return LEN(now);
	if(l <= nd[now].l && nd[now].r <= r)
	{
		if(nd[now].cover > 0) return LEN(now);
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
			if(nd[now].cover == 0) nd[now].sum = 0;
			else nd[now].sum = LEN(now);
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
	build(1, 1, sx-1);

	int low = 0, up = 0;
	for(int i=0; i<sy; ++i)
	{
		if(i > 0) ans += query(1, 1, sx-1) * (By[i] - By[i-1]);

		while(low < n && rt[pl[low]].y1 <= By[i])
		{
			if(rt[pl[low]].y1 == By[i])
			{
				int left = getID(rt[pl[low]].x1, sx) + 1, right = getID(rt[pl[low]].x2, sx);
				change(1, left, right, 1);
			}
			low++;
		}

		while(up < n && rt[pu[up]].y2 <= By[i])
		{
			if(rt[pu[up]].y2 == By[i])
			{
				int left = getID(rt[pu[up]].x1, sx) + 1, right = getID(rt[pu[up]].x2, sx);
				change(1, left, right, -1);
			}
			up++;
		}
	}

	return ans;
}

void solve()
{
	n = 0;
	while(true)
	{
		scanf("%d%d%d%d", &rt[n].x1, &rt[n].y1, &rt[n].x2, &rt[n].y2);
		if(rt[n].x1==-1 && rt[n].x2==-1 && rt[n].y1==-1 && rt[n].y2==-1) break;
		pl[n] = pu[n] = n;
		n++;
	}

	if(n == 0) return;

	int k1 = go();
	printf("%d\n", k1);
}

int main()
{
	while(true)
	{
		solve();
		if(n == 0) break;
	}
	return 0;
}

