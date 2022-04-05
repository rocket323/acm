#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 2010
#define ADD 2010
#define INF 0x3f3f3f3f
using namespace std;

int a[100010], b[maxl], n, m;
int f[2][2 * maxl], mat[maxl];

void init()
{
	for(int i=1; i<=m; ++i) scanf("%d", &a[i]);
	for(int i=1; i<=n; ++i) scanf("%d", &b[i]);

	sort(a + 1, a + 1 + m);
	sort(b + 1, b + 1 + n);
}

void solve()
{
	memset(f, 0x3f, sizeof f);
	
	int now = 1;
	for(int i=1; i<=n; ++i)
	{
		while(now < m && abs(a[now+1] - b[i]) < abs(a[now] - b[i])) now++;
		mat[i] = now;
	}

	/*
	for(int i=-n; i<=n; ++i)
	{
		int k = mat[1] + i;
		if(k < 1 || k > m) continue;

		f[0][i + ADD] = abs(a[k] - b[1]);
		f[0][i + ADD] = min(f[0][i + ADD], f[0][i + ADD - 1]);
	}
	*/

	int idx = 0, ans = INF;

	for(int i=-n; i<=n; ++i) f[0][i + ADD] = 0;

	//for(int i=1; i<=n; ++i) printf("%d ", mat[i]);
	//puts("");

	for(int i=1; i<=n; ++i)
	{
		idx ^= 1;
		memset(f[idx], 0x3f, sizeof f[idx]);
		for(int j=-n; j<=n; ++j)
		{
			int k = mat[i] + j;
			if(k < 1 || k > m) continue;

			int pre = k - 1 - mat[i-1];
			f[idx][j + ADD] = min(f[idx][j + ADD - 1], f[idx^1][pre + ADD] + abs(a[k] - b[i]));

			//printf("%d %d %d\n", i, k, f[idx][j + ADD]);

			if(i == n) ans = min(ans, f[idx][j + ADD]);
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d%d", &m, &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

