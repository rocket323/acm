#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 100010
#define INF 0x3f3f3f3f

struct Edge 
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxl * 2];

int f[maxl][2], mset, n, p[maxl];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<=n; ++i) adj[i].next = NULL;

	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
}

void dp(int now)
{
	int min_1 = INF, min_2 = INF, sum = 0;

	int cnt = 0;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] == k) continue;
		p[k] = now;

		dp(k);
		cnt++;

		sum += f[k][1];
		int tmp = f[k][0] - f[k][1];
		if(tmp < min_1){ min_2 = min_1; min_1 = tmp; }
		else if(tmp < min_2){ min_2 = tmp; }
	}

	f[now][0] = min(sum + cnt, sum + min_1 + cnt - 1);
	f[now][1] = min(sum + cnt, min(sum + min_1 + cnt - 1, sum + min_1 + min_2 + cnt - 2));
}

void solve()
{
	memset(f, 0x1f, sizeof f);
	memset(p, -1, sizeof p);
	dp(1);

	printf("%d\n", f[1][1] + 1);
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

