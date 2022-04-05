#include <stdio.h>
#include <cstring>
#define maxl 100010

int n, k, vis[maxl], A[maxl];

void solve()
{
	for(int i=0; i<n; ++i) scanf("%d", &A[i]);
	int len = 0, p = 0;
	while(true)
	{
		memset(vis, 0, sizeof vis);
		int cnt = 0;
		while(p < n && cnt < k)
		{
			if(!vis[A[p]]) cnt++, vis[A[p]] = 1;
			p++;
		}
		if(cnt < k) break;
		len++;
	}
	printf("%d\n", len + 1);
}

int main()
{
	while(scanf("%d%d", &n, &k) != EOF) solve();
	return 0;
}

