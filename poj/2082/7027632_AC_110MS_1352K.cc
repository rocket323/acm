#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 50010

int n, st[maxl], top, w[maxl], h[maxl], l[maxl], r[maxl], s[maxl];
int ans;

int main()
{
	while(scanf("%d", &n), n != -1)
	{
		s[0] = 0;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d%d", &w[i], &h[i]);
			s[i] = s[i-1] + w[i];
		}

		top = 0;
		for(int i=1; i<=n; ++i)
		{
			while(top > 0 && h[st[top-1]] >= h[i]) top--;
			if(top == 0) l[i] = s[i] - s[0];
			else l[i] = s[i] - s[st[top-1]];
			st[top++] = i;
		}
		top = 0;
		for(int i=n; i>=1; --i)
		{
			while(top > 0 && h[st[top-1]] >= h[i]) top--;
			if(top == 0) r[i] = s[n] - s[i-1];
			else r[i] = s[st[top-1]-1] - s[i-1];
			st[top++] = i;
		}

		ans = 0;
		for(int i=1; i<=n; ++i) ans = max(ans, h[i] * (l[i] + r[i] - w[i]));
		printf("%d\n", ans);
	}
	
	return 0;
}

