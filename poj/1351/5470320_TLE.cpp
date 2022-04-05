#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <cmath>

int n, ans;
int vis[5], a[19];

void dfs(int now, int cnt, bool dif)
{
	if(now==n+1)
	{
		if(cnt >= 3 && dif) ans++;
		return;
	}

	if(cnt + n - now < 2) return;

	int d = dif;
	for(int i=1; i<=4; ++i)
	{
		d = dif;
		a[now] = i;
		if(now > 1 && abs(i - a[now-1])==3) d = 1;

		int ad = 0;
		if(!vis[i])
		{
			vis[i] = 1;
			cnt++;
			ad = 1;
		}
		dfs(now+1, cnt, d);

		if(ad){ vis[i] = 0; cnt--; }
	}
}

void solve()
{
	printf("%d: ", n);
	memset(vis, 0, sizeof vis);
	ans = 0;
	dfs(1, 0, 0);
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n), n!=-1)
	{
		solve();
	}
	return 0;
}
