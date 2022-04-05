#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

int a[2010], b[2010], top, vis[2010], n, m;

void solve()
{
	memset(vis, 0, sizeof vis);
	for(int i=0; i<m; ++i)
	{
		scanf("%d", &a[i]);
		vis[a[i]] = 1;
	}

	top = 0;
	for(int i=1; i<=n*m; ++i) if(!vis[i]) b[top++] = i;

	sort(a, a+m);
	sort(b, b+n*m-m);

	int ans = m, p = 0;
	for(int i=0; i<m; ++i)
	{
		while(p < top && b[p] < a[i]) p++;
		if(b[p] > a[i])
		{
			ans--;
			p++;
		}
		else break;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n + m))
	{
		solve();
	}
}

