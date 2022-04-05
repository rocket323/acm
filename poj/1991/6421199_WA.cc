#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define min(a,b) ((a<b)?a:b)
#define maxl 1010
#define INF 0x3f3f3f3f

struct node
{
	int p, t;
}E[maxl];

int n, m, k, l;
int f[maxl][maxl][2], vis[maxl][maxl];

bool cmp(node A, node B)
{
	return A.p < B.p;
}

void init()
{
	scanf("%d%d%d", &n, &m, &l);
	for(int i=1; i<=n; ++i) scanf("%d%d", &E[i].p, &E[i].t);
	sort(E+1, E+1+n, cmp);
}

void dp(int a, int b)
{
	if(vis[a][b]) return;

	f[a][b][0] = f[a][b][1] = INF;

	if(a > 0)
	{
		dp(a-1, b);
		f[a][b][0] = min(f[a][b][0], max(f[a-1][b][0] + E[a].p - E[a-1].p, E[a].t));
		f[a][b][0] = min(f[a][b][0], max(f[a-1][b][1] + E[b].p - E[a].p, E[a].t));
	}

	if(b <= n)
	{
		dp(a, b+1);
		f[a][b][1] = min(f[a][b][1], max(f[a][b+1][1] + E[b+1].p - E[b].p, E[b].t));
		f[a][b][1] = min(f[a][b][1], max(f[a][b+1][0] + E[b].p - E[a].p, E[b].t));
	}

	vis[a][b] = 1;
}

void solve()
{
	memset(vis, 0, sizeof vis);
	vis[0][n+1] = 1;
	f[0][n+1][0] = 0;
	f[0][n+1][1] = INF;

	int ans = INF;
	for(int i=0; i<=n; ++i)
	{
		dp(i, i+1);
		if(i != 0) ans = min(ans, f[i][i+1][0] + abs(l - E[i].p));
		if(i != n) ans = min(ans, f[i][i+1][0] + abs(l - E[i+1].p));
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}

