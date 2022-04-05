#include <stdio.h>
#include <cstring>

int n, m, f[13][1<<13];

int check(int i, int p)
{
	return (i & (1<<p));
}

void dfs(int row, int pos, int old, int nxt)
{
	if(pos==m)
	{
		f[row+1][nxt] += f[row][old];
		return;
	}

	if(pos<m-1 && !check(old, pos) && !check(old, pos+1)) dfs(row, pos+2, old, nxt);

	if(!check(old, pos)) dfs(row, pos+1, old, nxt|(1<<pos));

	if(check(old, pos)) dfs(row, pos+1, old, nxt);
}

void solve()
{
	memset(f, 0, sizeof f);
	f[1][0] = 1;

	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<(1<<m); ++j)
		{
			dfs(i, 0, j, 0);
		}
	}
	printf("%d\n", f[n+1][0]);
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n+m)) solve();
	return 0;
}
