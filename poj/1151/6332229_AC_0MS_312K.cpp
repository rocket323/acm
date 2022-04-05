//poj1151 picture
//求N个矩形并的面积

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxl 5020
#define eps (1e-8)
#define min(a,b) ((a<b)?a:b)
#define LEN(now) (Bx[nd[(now)].r] - Bx[nd[(now)].l-1])

struct rect
{
	double x1, y1, x2, y2;
}rt[maxl];

struct node
{
	int l, r;
	int cover;
	double sum;
}nd[8 * maxl];

int n, ans, pl[maxl], pu[maxl], sx, sy;
vector<double> Bx(maxl), By(maxl);

bool cmpLow(int x, int y){ return rt[x].y1 < rt[y].y1; }
bool cmpHigh(int x, int y){ return rt[x].y2 < rt[y].y2; }

int getID(double x, int size)
{
	int low = 0, high = size - 1, mid, ans = -1;

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(Bx[mid] <= x + eps)
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

double query(int now, int l, int r)
{
	if(nd[now].cover > 0) return LEN(now);
	if(l <= nd[now].l && nd[now].r <= r)
	{
		if(nd[now].cover > 0) return LEN(now);
		else return nd[now].sum;
	}

	double lv = 0, rv = 0;
	int mid = (nd[now].l + nd[now].r) / 2;
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

double go()
{
	double ans = 0;

	init();
	build(1, 1, sx-1);

	int low = 0, up = 0;
	for(int i=0; i<sy; ++i)
	{
		if(i > 0) ans += query(1, 1, sx-1) * (By[i] - By[i-1]);

		while(low < n && rt[pl[low]].y1 <= By[i] + eps)
		{
			if(rt[pl[low]].y1 == By[i])
			{
				int left = getID(rt[pl[low]].x1, sx) + 1, right = getID(rt[pl[low]].x2, sx);
				change(1, left, right, 1);
			}
			low++;
		}

		while(up < n && rt[pu[up]].y2 <= By[i] + eps)
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
	for(int i=0; i<n; ++i)
	{
		scanf("%lf%lf%lf%lf", &rt[i].x1, &rt[i].y1, &rt[i].x2, &rt[i].y2);
		pl[i] = pu[i] = i;
	}

	double k1 = go();
	printf("Total explored area: %.2lf\n\n", k1);
}

int main()
{
	int tc = 0;
	while(scanf("%d", &n), n)
	{
		printf("Test case #%d\n", ++tc);
		solve();
		if(n == 0) break;
	}
	return 0;
}

