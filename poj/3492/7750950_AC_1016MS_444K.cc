/*
 * =======================================================
 *       Filename:  3492.cpp
 *    Description:  
 *        Created:  16/10/10 09:52:02
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define maxl 6010

int d[maxl], vis[maxl];
int n, a[maxl], sum, mx;

void solve()
{
	memset(d, 0x3f, sizeof d);
	for(int i=1; i<=n; ++i) d[a[i] % a[1]] = min(d[a[i] % a[1]], a[i]);

	memset(vis, 0, sizeof vis);
	for(int x=0; x<a[1]; ++x)
	{
		int val = INF, k = -1;
		for(int i=0; i<a[1]; ++i)
		{
			if(!vis[i] && d[i] < val)
			{
				val = d[i];
				k = i;
			}
		}
		if(k == -1) break;
		vis[k] = 1;
		for(int i=1; i<=n; ++i)
		{
			int p = (k + a[i]) % a[1], v = d[k] + a[i];
			d[p] = min(d[p], v);
		}
	}
	int rec = 0;
	for(int i=0; i<a[1]; ++i) rec = max(rec, d[i]);
	printf("%d\n", rec - a[1]);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		int g = -1;
		mx = 0;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d", &a[i]);
			if(g == -1) g = a[i];
			else g = __gcd(g, a[i]);
			if(a[i] > mx) mx = a[i];
		}

		if(g != 1)
		{
			puts("INF");
			continue;
		}
		solve();
	}
	return 0;
}

