#include <stdio.h>
#include <cstring>
#include <math.h>
#define maxl 1000010
#define INF 0x3f3f3f3f
#define ll long long
#define min(a,b) ((a<b)?a:b)

int f[maxl], n, x[maxl], y[maxl];

void init()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d%d", &x[i], &y[i]);
	memset(f, 0x3f, sizeof f);
}

int go(int i)
{
	return (int)sqrt((ll)y[i]*y[i] - ((ll)(y[i]-y[1]) * (y[i]-y[1])));
}

void solve()
{
	f[x[1]] = 0;

	for(int i=2; i<=n; ++i)
	{
		int k = go(i);
		for(int j=x[i]-k; j<x[i]; ++j)
		{
			if(j>=x[1] && 2*x[i]-j<=x[n]) f[2*x[i]-j] = min(f[2*x[i]-j], f[j] + 1);
			if(j>=x[1] && 2*x[i]-j>x[n]) f[x[n]] = min(f[x[n]], f[j] + 1);
		}
	}
	//for(int i=x[1]; i<=x[n]; ++i) printf("%d ", f[i]);
	//puts("");
	if(f[x[n]] < INF) printf("%d\n", f[x[n]]);
	else puts("-1");
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

