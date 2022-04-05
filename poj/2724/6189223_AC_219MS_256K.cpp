#include <stdio.h>
#include <map>
#include <cstring>
using namespace std;

struct Edge
{
	int idx;
	Edge *next;
}
adj[2000], memo[200000];

char str[11];
int vis[2000], st[2000], top, mset;
int mark[2000], m, n, lik[2000];

void addEdge(int a, int b)
{
	//printf("%d %d\n", a, b);
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

int find(char str[])
{
	for(int i=0; str[i]; ++i)
	{
		if(str[i] == '*') return i;
	}
	return -1;
}

int getNum(char str[])
{
	int ans = 0;
	for(int i=0; str[i]; ++i)
	{
		ans = ans * 2 + str[i] - '0';
	}
	return ans;
}

void init()
{
	memset(vis, 0, sizeof vis);
	top = 0;
	for(int i=0; i<m; ++i)
	{
		scanf("%s", str);
		int k = find(str);
		if(k != -1)
		{
			str[k] = '0';
			int n1 = getNum(str);
			if(!vis[n1]) st[top++] = n1;
			vis[n1] = 1;
			str[k] = '1';

			int n2 = getNum(str);
			if(!vis[n2]) st[top++] = n2;
			vis[n2] = 1;
		}
		else
		{
			int n1 = getNum(str);
			if(!vis[n1]) st[top++] = n1;
			vis[n1] = 1;
		}
	}
}

void dfs(int now, int col)
{
	mark[now] = col;
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(mark[k] == -1) dfs(k, col^1);
	}
}

bool can(int now)
{
	for(Edge *ptr=adj[now].next; ptr; ptr=ptr->next)
	{
		int k = ptr->idx;
		if(mark[k] == 1 && !vis[k])
		{
			vis[k] = 1;
			if(lik[k] == -1 || can(lik[k]))
			{
				lik[k] = now;
				return 1;
			}
		}
	}
	return 0;
}

int max_match()
{
	int ans = 0;
	memset(lik, -1, sizeof lik);
	for(int i=0; i<top; ++i)
	{
		if(mark[st[i]] == 0)
		{
			memset(vis, 0, sizeof vis);
			if(can(st[i])) ans++;
		}
	}
	return ans;
}

bool check(int a, int b)
{
	int cnt = 0;
	while(a || b)
	{
		cnt += ((a % 2) != (b % 2));
		a /= 2;
		b /= 2;
	}
	return cnt == 1;
}

void solve()
{
	for(int i=0; i<(1<<n); ++i) adj[i].next = NULL;
	mset = 0;

	for(int i=0; i<top; ++i)
	{
		for(int j=0; j<top; ++j)
			if(check(st[i], st[j])) addEdge(st[i], st[j]);
	}

	memset(mark, -1, sizeof mark);
	for(int i=0; i<top; ++i)
	{
		if(mark[st[i]] != -1) continue;
		dfs(st[i], 0);
	}

	printf("%d\n", top - max_match());
}

int main()
{
	while(scanf("%d%d", &n, &m) && (n + m))
	{
		init();
		solve();
	}
	return 0;
}
