#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define Min(a,b) ((a<b)?a:b)
#define maxl 220
#define INF 0x3f3f3f3f

int a[maxl], top, p[maxl], ave[maxl], n, b[maxl];

void init()
{
	top = 0;
	for(int i=0; i<n; ++i)
	{
		scanf("%d", &p[i]);
		a[top++] = p[i];
		a[top++] = p[i] - 1;
	}
	for(int i=1; i<=n; ++i) scanf("%d", &ave[i]);

	sort(a, a+top);

	int i, j;
	for(i=1, j=1; j<top; ++j) if(a[j] != a[i-1]) a[i++] = a[j];
	top = i;
}

int calc(int x, int y)
{
	for(int i=0; i<=x; ++i) b[i] = p[i];
	b[x+1] = y;
	for(int i=x+1; i<n; ++i) b[i+1] = p[i];

	int ans = 0, min = b[0];
	for(int i=1; i<=x; ++i) min = Min(min, b[i]);
	if(min >= b[x+1])
	{
		ans += y * ave[x+2];
		for(int i=x+2; i<n; ++i)
		{
			if(b[i] > y) ans += y * ave[i+1];
			else break;
		}
	}
	min = b[n];
	for(int i=n-1; i>x+1; --i) min = Min(min, b[i]);
	if(min >= b[x+1])
	{
		ans += y * ave[n-x];
		for(int i=x; i>0; --i)
		{
			if(b[i] > y) ans += y * ave[n+1-i];
			else break;
		}
	}
	return ans;
}

void solve()
{
	int ans = -1, ra, rb;
	for(int i=0; i<=n-1; ++i)
	{
		for(int j=0; j<top-1; ++j)
		{
			int k = calc(i, a[j]);
			if(k > ans || k == ans && (i < ra || i == ra && a[j] < rb))
			{
				ans = k;
				ra = i;
				rb = a[j];
			}
		}
	}
	printf("%d %d\n", ra+1, rb);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

