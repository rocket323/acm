#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 10010

int n, f[maxl], t[maxl];
vector<int> adj[maxl];

void init()
{
	for(int i=1; i<=n; ++i) adj[i].clear();

	int k, a;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d", &t[i], &k);
		for(int j=0; j<k; ++j)
		{
			scanf("%d", &a);
			adj[i].push_back(a);
		}
	}
}

void solve()
{
	int ans = 0;
	memset(f, 0x3f, sizeof f);
	f[1] = t[1];
	for(int i=1; i<=n; ++i)
	{
		f[i] = t[i];
		for(int j=0; j<adj[i].size(); ++j)
		{
			int k = adj[i][j];
			f[i] = max(f[i], f[k] + t[i]);
		}
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
	return 0;
}

