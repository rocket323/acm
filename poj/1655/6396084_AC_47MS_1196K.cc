#include <stdio.h>
#include <cstring>
#define maxl 20010
#define INF 0x3f3f3f3f

struct Edge
{
	int idx;
	Edge *next;
}
adj[maxl], memo[maxl * 2];

int n, p[maxl], mset, s[maxl];

void addEdge(int a, int b)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	scanf("%d", &n);
	mset = 0;
	for(int i=1; i<=n; ++i) adj[i].next = NULL;
	for(int i=0; i<n-1; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}

	/*
	for(int i=1; i<=n; ++i)
	{
		printf("%d : ", i);
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			printf("%d ", ptr->idx);
		}
		puts("");
	}
	*/
}

int calc(int idx)
{
	int max = 0;
	for(Edge *ptr=adj[idx].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[k] != idx) continue;
		if(s[k] > max) max = s[k];
	}
	if(p[idx] != -1)
	{
		int u = p[idx];
		int tmp = n - s[idx];
		if(tmp > max) max = tmp;
	}
	//printf("%d %d\n", idx, max);
	return max;
}

void dfs(int now)
{
	s[now] = 1;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(p[now] != k)
		{
			p[k] = now;
			dfs(k);
			s[now] += s[k];
		}
	}
}

void solve()
{
	memset(p, -1, sizeof p);
	memset(s, 0, sizeof s);
	dfs(1);

	int ans = INF, rec = -1;
	for(int i=1; i<=n; ++i)
	{
		int k = calc(i);
		if(k < ans)
		{
			ans = k;
			rec = i;
		}
	}

	printf("%d %d\n", rec, ans);
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

