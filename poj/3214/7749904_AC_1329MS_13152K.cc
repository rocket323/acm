/*
 * =======================================================
 *       Filename:  3214.cpp
 *    Description:  
 *        Created:  16/10/10 00:07:42
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1200010
#define INF 0x3f3f3f3f

int n, h, num[maxl], a[maxl], cnt, tmp;
int f[maxl], Q[maxl], top;

void dfs(int now)
{
	if(now * 2 <= n) dfs(now * 2);
	if(now * 2 + 1 <= n)
	{
		tmp++;
		dfs(now * 2 + 1);
	}
	a[++cnt] = num[now] - tmp;
}

void out()
{
	for(int i=0; i<top; ++i) printf("%d ", Q[i]);
	puts("");
}

int main()
{
	scanf("%d", &h);
	n = 0;
	while(scanf("%d", &num[++n]) != EOF);
	--n;
	tmp = 0;
	dfs(1);

	//for(int i=1; i<=n; ++i) printf("%d ", a[i]);
	//puts("");

	top = 0;
	Q[top++] = 0;
	a[0] = -INF;
	f[0] = 0;

	int rec = -INF;
	for(int i=1; i<=n; ++i)
	{
		int l = 0, r = top - 1, p = -1, mid;
		//printf("%d : ", i);
		//out();
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(a[Q[mid]] <= a[i])
			{
				p = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		f[i] = f[Q[p]] + 1;
		rec = max(rec, f[i]);
		Q[p + 1] = i;
		if(p + 1 == top) top++;
	}

	printf("%d\n", n - rec);

	return 0;
}

