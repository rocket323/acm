#include <stdio.h>
#include <cstring>
#define maxl 1010
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

int n, c, l, t[maxl], ans;
int f[maxl][maxl], sum[maxl], g[maxl];

void init()
{
	scanf("%d%d", &l, &c);
	sum[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &t[i]);
		sum[i] = sum[i-1] + t[i];
	}

	int time = l;
	ans = 1;
	g[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		if(time >= t[i]) time -= t[i];
		else
		{
			ans++;
			time = l - t[i];
		}
		g[i] = ans;
	}
}

int dp(int n, int m)
{
	if(f[n][m] != -1) return f[n][m];
	if(n == 0 || m == 0) return INF;

	f[n][m] = INF;
	int st = n-1;
	while(g[st] > m-1 && st >= 0) st--;
	for(int i=st; i>=0 && sum[n]-sum[i]<=l; --i)
	{
		int w, k = l - sum[n] + sum[i];
		if(k == 0) w = 0;
		else if(k <= 10) w = -c;
		else w = (k - 10) * (k - 10);
		f[n][m] = min(f[n][m], dp(i, m-1) + w);
	}
	return f[n][m];
}

void solve()
{
	printf("Minimum number of lectures: %d\n", ans);

	memset(f, -1, sizeof f);
	f[0][0] = 0;

	printf("Total dissatisfaction index: %d\n", dp(n, ans));
}

int main()
{
	int tc = 0;
	while(scanf("%d", &n), n)
	{
		if(tc) puts("");
		printf("Case %d:\n\n", ++tc);
		init();
		solve();
	}
	return 0;
}

