#include <stdio.h>
#include <cstring>
#define INF 0x7f7f7f7f
#define MaxL 100010

int g[MaxL], f[MaxL], n, a[MaxL], s[MaxL];

int Max(int a, int b){ return (a>b)?a:b; }

void init()
{
	s[0] = 0;
	g[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &a[i]);
		s[i] = s[i-1] + a[i];
		g[i] = Max(g[i-1] + a[i], a[i]);
		g[i] = Max(g[i], g[i-1]);
	}
}

void solve()
{
	int ans = -INF;
	int l = Max(0, g[1]-s[1]);
	for(int i=2; i<=n; ++i)
	{
		f[i] = s[i] + l;
		if(f[i] > ans) ans = f[i];
		l = Max(l, g[i]-s[i]);
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) && n)
	{
		init();
		solve();
	}
	return 0;
}
