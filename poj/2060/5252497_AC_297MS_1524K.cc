#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#define MaxL 501
using namespace std;

struct Edge
{
	int idx;
	Edge * next;
}
adj[MaxL], memo[250010];

int n, mset;
int s[MaxL], t[MaxL];
int lik[MaxL], vis[MaxL];
int x1[MaxL], y1[MaxL], x2[MaxL], y2[MaxL];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{

	int a, b;
	char ch;

	scanf("%d", &n);
	for(int i=1; i<=n; ++i)
	{
		char str[10];
		scanf("%s", str);
		istringstream in(str);
		in >> a >> ch >> b;
		s[i] = 60 * a + b;
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
		t[i] = s[i] + abs(x1[i]-x2[i]) + abs(y1[i]-y2[i]);
	}
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			if(t[i] + abs(x2[i]-x1[j]) + abs(y2[i]-y1[j]) < s[j]) addEdge(i, j);
		}
	}
}

bool can(int now)
{
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(!vis[k])
		{
			vis[k] = 1;
			if(lik[k]==-1 || can(lik[k]))
			{
				lik[k] = now;
				return 1;
			}
		}
	}
	return 0;
}

void solve()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=1; i<=n; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(can(i)) ans++;
	}
	ans = n - ans;
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
