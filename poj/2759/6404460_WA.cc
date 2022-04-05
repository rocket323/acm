#include <stdio.h>
#include <cstring>
#define maxl 10010
#define INF 0x3f3f3f3f

int n, m, a[2][maxl], s[3][maxl], sum;
int f[maxl], g[maxl], p[3][maxl], low;

int min(int a, int b){ return (a < b) ? a : b; }
int max(int a, int b){ return (a > b) ? a : b; }

void init()
{
	scanf("%d%d", &n, &m);
	low = -INF;
	sum = 0;
	for(int i=0; i<2; ++i)
	{
		s[i][0] = 0;
		for(int j=1; j<=n; ++j)
		{
			scanf("%d", &a[i][j]);
			sum += a[i][j];
			low = max(low, a[i][j]);
			s[i][j] = s[i][j-1] + a[i][j];
		}
	}
	for(int i=0; i<=n; ++i) s[2][i] = s[0][i] + s[1][i];
}

bool check(int lim)
{
	//printf("n %d\n", lim);
	int flag = 0;
	if(lim == 12) flag = 1;
	for(int i=0; i<3; ++i)
	{
		int k = 0;
		p[i][0] = -1;
		for(int j=1; j<=n; ++j)
		{
			while(s[i][j] - s[i][k] > lim) k++;
			p[i][j] = k;
			//if(flag) printf("%d ", p[i][j]);
		}
		//if(flag) printf("\n");
	}

	f[0] = g[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		f[i] = INF;
		for(int j=p[2][i]; j>=0; j=p[2][j])
		{
			f[i] = min(f[i], f[j] + 1);
			f[i] = min(f[i], g[j] + 1);
			if(j == p[2][j]) break;
		}

		g[i] = INF;
		int a = p[0][i], b = p[1][i], c = 2;
		while(a != b)
		{
			g[i] = min(g[i], g[max(a, b)] + c - 1);
			g[i] = min(g[i], f[max(a, b)] + c - 1);
			if(a > b) a = p[0][a];
			else b = p[1][b];
			c++;
		}
		g[i] = min(g[i], g[a] + c);
		g[i] = min(g[i], f[a] + c);
	}
	return min(f[n], g[n]) <= m;
}

void solve()
{
	int l = low, r = sum, mid, ans = -1;
	//printf("%d %d\n", l, r);
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(check(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else l = mid + 1;
	}

	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}

