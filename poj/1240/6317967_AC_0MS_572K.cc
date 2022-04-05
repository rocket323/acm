#include <stdio.h>
#include <cstring>
#include <stdlib.h>

bool vis[100];
char s[100], t[100];
int n, c[21][21], m, son[100];

void get_c()
{
	for(int i=0; i<=20; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j=1; j<i; ++j) c[i][j] = c[i-1][j] + c[i-1][j-1];
	}
}

void dfs(int sa, int sb, int ta, int tb)
{
	int r = s[sa] - 'a';
	vis[sa] = 1;

	int p = ta;
	for(int i=sa+1; i<=sb; ++i)
	{
		if(vis[i]) continue;

		int cnt = 0;
		while(true)
		{
			cnt++;
			if(t[p] == s[i]) break;
			p++;
		}

		son[r]++;

		dfs(i, i+cnt-1, p-cnt+1, p);
		p++;
	}
}

void init()
{
	scanf("%s%s", s, t);
	n = strlen(s);

	memset(son, 0, sizeof son);
	memset(vis, 0, sizeof vis);

	dfs(0, n-1, 0, n-1);
}

void solve()
{
	int ans = 1;
	for(int i=0; i<n; ++i)
	{
		ans *= c[m][son[i]];
	}
	printf("%d\n", ans);
}

int main()
{
	get_c();
	while(scanf("%d", &m), m)
	{
		init();
		solve();
	}
	return 0;
}

