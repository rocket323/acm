#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 1010

int n, a[maxl], b[maxl], c[maxl], f[maxl][maxl], w[maxl];
vector<int> s[maxl];
vector<int> :: iterator it;

void init()
{
	for(int i=0; i<maxl; ++i) s[i].clear();
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d%d", &a[i], &b[i], &w[i]);
		s[b[i]].push_back(i);
	}
}

void solve()
{
	memset(f, 0, sizeof f);

	for(int i=0; i<=365; ++i)
	{
		for(int x=0; x<s[i].size(); ++x)
		{
			int k = s[i][x];
			for(int j=0; j<i; ++j)
			{
				f[i][j] = max(f[i][j], f[a[k] - 1][j] + w[k]);
			}

			for(int y=x+1; y<s[i].size(); ++y)
			{
				int l = s[i][y];
				f[i][i] = max(f[i][i], f[a[k] - 1][a[l] - 1] + w[k] + w[l]);
			}
		}

		for(int j=0; j<=i; ++j)
		{
			if(i) f[i][j] = max(f[i][j], f[i-1][j]);
			if(j) f[i][j] = max(f[i][j], f[i][j-1]);
			if(i && j) f[i][j] = max(f[i][j], f[i-1][j-1]);
			f[j][i] = f[i][j];
		}
	}
	printf("%d\n", f[365][365]);
}

int main()
{
	while(scanf("%d", &n), n)
	{
		init();
		solve();
	}
	return 0;
}

