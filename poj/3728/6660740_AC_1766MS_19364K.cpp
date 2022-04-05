#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 50010
#define maxd 16

int n, w[maxl], ans1[maxl][maxd], ans2[maxl][maxd], maxw[maxl][maxd], minw[maxl][maxd], d[maxl];
int p[maxl][maxd], m;
vector<int> adj[maxl];

void dfs(int now)
{
	for(int i=0; i<adj[now].size(); ++i)
	{
		int k = adj[now][i];
		if(p[now][0] != k)
		{
			d[k] = d[now] + 1;
			p[k][0] = now;
			dfs(k);
		}
	}
}

void init()
{
	for(int i=0; i<n; ++i) scanf("%d", &w[i]);

	for(int i=0; i<n; ++i) adj[i].clear();
	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}

	memset(p, -1, sizeof p);
	d[0] = 0;
	dfs(0);

	for(int i=1; i<n; ++i)
	{
		maxw[i][0] = max(w[i], w[p[i][0]]);
		minw[i][0] = min(w[i], w[p[i][0]]);
		ans1[i][0] = w[p[i][0]] - w[i];
		ans2[i][0] = w[i] - w[p[i][0]];
	}

	for(int k=1; (1<<k)<=n; ++k)
	{
		for(int i=0; i<n; ++i) if(p[i][k-1] != -1)
		{
			p[i][k] = p[p[i][k-1]][k-1];
			maxw[i][k] = max(maxw[i][k-1], maxw[p[i][k-1]][k-1]);
			minw[i][k] = min(minw[i][k-1], minw[p[i][k-1]][k-1]);
			ans1[i][k] = max(maxw[p[i][k-1]][k-1] - minw[i][k-1], max(ans1[i][k-1], ans1[p[i][k-1]][k-1]));
			ans2[i][k] = max(maxw[i][k-1] - minw[p[i][k-1]][k-1], max(ans2[i][k-1], ans2[p[i][k-1]][k-1]));
		}
	}
}

int lca(int a, int b)
{
	if(d[a] < d[b]) swap(a, b);
	int dif = d[a] - d[b];
	for(int i=15; i>=0; --i)
	{
		if(dif & (1<<i)) a = p[a][i];
	}

	for(int i=15; i>=0; --i)
	{
		if(d[a] >= (1<<i) && p[a][i] != p[b][i])
		{
			a = p[a][i];
			b = p[b][i];
		}
	}
	if(a == b) return a;
	else return p[a][0];
}

void solve()
{
	scanf("%d", &m);

	for(int i=0; i<m; ++i)
	{
		int a, b, c;
		scanf("%d%d", &a, &b);
		a--, b--;

		c = lca(a, b);

		int ans = 0, tmin = w[a], tmax = w[b];
		for(int i=15; i>=0; --i) if(d[a] - d[c] >= (1<<i))
		{
			ans = max(ans, ans1[a][i]);
			ans = max(ans, maxw[a][i] - tmin);
			tmin = min(tmin, minw[a][i]);
			a = p[a][i];
		}

		for(int i=15; i>=0; --i) if(d[b] - d[c] >= (1<<i))
		{
			ans = max(ans, ans2[b][i]);
			ans = max(ans, tmax - minw[b][i]);
			tmax = max(tmax, maxw[b][i]);
			b = p[b][i];
		}
		ans = max(ans, tmax - tmin);

		printf("%d\n", ans);
	}
}

int main()
{
	scanf("%d", &n);
	init();
	solve();
	return 0;
}

