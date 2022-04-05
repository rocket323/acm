/*
 * =======================================================
 *       Filename:  1457.cpp
 *    Description:  
 *        Created:  24/10/10 23:06:56
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define INF 1200000000

int s[1001000], sum[10000], n, t, ans;
int list[10000], vis[1000000];

void dfs(int now, int pro, int st)
{
	if(now == n + 1)
	{
		ans = pro;
		//for(int i=1; i<=n; ++i) printf("%d ", list[i]);
		//puts("");
		return;
	}
	for(int i=0; i<t; ++i)
	{
		if(vis[i]) continue;
		sum[now] = sum[now - 1] + s[i];
		list[now] = s[i];
		int flag = 1;
		for(int a=0; a<=now && flag; ++a)
		for(int b=a+1; b<=now && flag; ++b)
		{
			int x = sum[b] - sum[a];
			int pos = lower_bound(s, s + t, x) - s;
			if(pos == t || s[pos] != x) flag = 0;
		}
		if(!flag) continue;
		if(s[i] > INF / pro) break;
		vis[i] = 1;
		dfs(now + 1, pro * s[i], i + 1);
		vis[i] = 0;
		if(ans != -1) return;
	}
}

void solve()
{

	for(n=1; n * (n + 1) / 2 != t; ++n);
	for(int i=0; i<t; ++i) vis[i] = 0;
	ans = -1;
	sum[0] = 0;
	dfs(1, 1, 0);
	if(ans == -1) puts("No solution");
	else printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &t) != EOF)
	{
		for(int i=0; i<t; ++i) scanf("%d", &s[i]);

		solve();
	}
}

