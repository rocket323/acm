#include <iostream>
#define mod 1000000007
#include <cstring>

int n, m;
int f[4501][4501];

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			f[i][j] = (f[i][j] + f[i-1][j-1]) % mod;
			if(i>=j) f[i][j] = (f[i][j] + f[i-j][j]) % mod;
		}
	}
	int ans = 0;
	for(int i=1; i<=m; ++i) ans = (ans + f[n][i]) % mod;
	printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &m, &n);
	solve();
	return 0;
}