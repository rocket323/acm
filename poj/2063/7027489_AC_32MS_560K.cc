#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxn 50000

int a[20], b[20], f[maxn], n, m, k;

void init()
{
	scanf("%d%d", &n, &m);
	scanf("%d", &k);
	for(int i=1; i<=k; ++i)
	{
		scanf("%d%d", &a[i], &b[i]);
	}
}

void solve()
{
	memset(f, 0, sizeof f);
	for(int i=1; i<=k; ++i)
	{
		for(int j=a[i]/1000; j<maxn; ++j)
		{
			f[j] = max(f[j], f[j-a[i]/1000] + b[i]);
		}
	}

	int ans = n;
	for(int i=1; i<=m; ++i)
	{
		ans += f[ans/1000];
	}
	printf("%d\n", ans);
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

