#include <stdio.h>
#include <algorithm>
#define MaxL 20010
using namespace std;

int n, m, a[MaxL], b[MaxL];

void solve()
{
	int ans = 0, p = 0;
	for(int i=0; i<n; ++i)
	{
		while(p<m && b[p]<a[i]) p++;
		if(p==m)
		{
			printf("Loowater is doomed!\n");
			return;
		}
		ans += b[p++];
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n+m))
	{
		for(int i=0; i<n; ++i) scanf("%d", &a[i]);
		for(int i=0; i<m; ++i) scanf("%d", &b[i]);
		sort(a, a+n);
		sort(b, b+m);
		solve();
	}
	return 0;
}
