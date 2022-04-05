#include <stdio.h>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
#define maxl 520
using namespace std;

int n, x[maxl], y[maxl], d[maxl], p[maxl];

int dist(int a, int b)
{
	return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

bool cmp(int a, int b)
{
	return d[a] > d[b];
}

void update(int& a, int& b, int c)
{
	if(c > a)
	{
		b = a;
		a = c;
	}
	else if(c > b)
	{
		b = c;
	}
}

void solve()
{
	int ans = INF;
	for(int i=0; i<n; ++i)
	{
		for(int k=0; k<n; ++k) p[k] = k, d[k] = dist(i, k);
		sort(p, p + n, cmp);

		for(int j=i+1; j<n; ++j)
		{

			int l1 = 0, l2 = 0, r1 = 0, r2 = 0;
			for(int k=0; k<n; ++k)
			{
				if(k == n-1) r1 = d[p[k]], r2 = 0;
				else r1 = d[p[k]], r2 = d[p[k+1]];
				ans = min(ans, max(l1 + l2, max(r1 + r2, r1 + l1 + dist(i, j))));
				update(l1, l2, dist(j, p[k]));
			}
		}
	}

	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i=0; i<n; ++i) scanf("%d%d", &x[i], &y[i]);
		solve();
	}
	return 0;
}
