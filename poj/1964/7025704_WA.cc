#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1010

int n, m, h[maxl], l[maxl], r[maxl], st[maxl], top;
char a[maxl][maxl];

void init()
{
	scanf("%d%d", &n, &m);
	getchar();
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			scanf("%c", &a[i][j]);
			getchar();
		}
	}
}

void solve()
{
	memset(h, 0, sizeof h);

	int ans = 0;
	for(int i=0; i<n; ++i)
	{
		top = 0;
		for(int j=0; j<m; ++j)
		{
			if(a[i][j] == 'F') h[j]++; else h[j] = 0;
			while(top > 0 && h[st[top-1]] >= h[j]) top--;
			if(top == 0) l[j] = h[j] * (j + 1);
			else l[j] = h[j] * (j - st[top - 1]);
			st[top++] = j;
		}

		top = 0;
		for(int j=m-1; j>=0; --j)
		{
			while(top > 0 && h[st[top-1]] >= h[j]) top--;
			if(top == 0) r[j] = h[j] * (m - j);
			else r[j] = h[j] * (st[top - 1] - j);
			st[top++] = j;
		}

		for(int j=0; j<m; ++j) ans = max(ans, l[j] + r[j] - h[j]);
	}

	printf("%d\n", ans * 3);
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

