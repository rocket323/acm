#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 1010

vector<int> adj[maxl];
vector<int> list;
int n, m, f[maxl];

void init()
{
	for(int i=0; i<n; ++i)
	{
		adj[i].clear();
		int k, a;
		scanf("%d", &k);
		for(int j=0; j<k; ++j)
		{
			scanf("%d", &a);
			adj[i].push_back(a);
		}
	}

	memset(f, -1, sizeof f);
}

int sg(int now)
{
	if(f[now] != -1) return f[now];
	for(int i=0; i<adj[now].size(); ++i) sg(adj[now][i]);

	list.clear();
	for(int i=0; i<adj[now].size(); ++i) list.push_back(f[adj[now][i]]);

	if(list.begin() == list.end()) return f[now] = 0;
	else
	{
		sort(list.begin(), list.end());
		if(list[0] != 0) return f[now] = 0;
		else
		{
			for(int i=1; i<list.size(); ++i) if(list[i] > list[i-1] + 1) return f[now] = list[i-1] + 1;
			return f[now] = list[list.size()-1] + 1;
		}
	}
}

void solve()
{
	for(int i=0; i<n; ++i) if(f[i] == -1) f[i] = sg(i);
	while(scanf("%d", &m), m)
	{
		int sum = 0, a;
		for(int i=0; i<m; ++i)
		{
			scanf("%d", &a);
			sum ^= f[a];
		}
		if(sum == 0) puts("LOSE");
		else puts("WIN");
	}
}

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		init();
		solve();
	}
}

