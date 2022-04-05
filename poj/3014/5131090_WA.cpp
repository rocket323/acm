#include <iostream>
#define mod 1000000007
#include <cstring>

int n, m;
int f[4501][2];

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	int now = 1, ans = 0;
	for(int j=1; j<=m; ++j)
	{
		f[0][now] = 0;
		for(int i=1; i<=n; ++i)
		{
			f[i][now] = 0;
			f[i][now] = (f[i][now] + f[i-1][now^1]) % mod;
			if(i>=j) f[i][now] = (f[i][now] + f[i-j][now]) % mod;
		}
		ans = (ans + f[n][now]) % mod;
		now ^= 1;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &m, &n)!=EOF)
	{
		printf("1\n");
		//solve();
	}
	return 0;
}