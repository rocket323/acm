#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 2000

struct Edge
{
	int idx, vis;
	Edge *next;
}
adj1[maxl], adj2[maxl], memo[maxl * 8];

char s[3010], t[3010], f[maxl][maxl];
int n, m, pos, len, mset, son_a[maxl], son_b[maxl];

void addEdge(Edge adj[], int a, int b, int son[])
{
	son[a]++;
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void dfs(char s[], int now, Edge adj[], int & n, int son[])
{
	if(pos == len) return;
	while(pos < len)
	{
		if(s[pos] == '0')
		{
			addEdge(adj, now, n++, son);
			pos++;
			dfs(s, n-1, adj, n, son);
		}
		else
		{
			pos++;
			break;
		}
	}
}

void init()
{
	scanf("%s", s);
	scanf("%s", t);

	len = strlen(s);
	if(len != strlen(t)) return;

	mset = 0;
	for(int i=0; i<=len/2; ++i) adj1[i].next = adj2[i].next = NULL;
	memset(son_a, 0, sizeof son_a);
	memset(son_b, 0, sizeof son_b);

	n = 1, m = 1;
	pos = 0;
	dfs(s, 0, adj1, n, son_a);
	pos = 0;
	dfs(t, 0, adj2, m, son_b);
}

int dp(int a, int b)
{
	if(f[a][b] != -1) return f[a][b];
	if(son_a[a] != son_b[b]) return f[a][b] = 0;

	f[a][b] = 1;
	for(Edge *ptr=adj2[b].next; ptr; ptr=ptr->next) ptr->vis = 0;

	for(Edge *ptr=adj1[a].next; ptr; ptr=ptr->next)
	{
		int flag = 0;
		for(Edge *ptr2=adj2[b].next; ptr2; ptr2=ptr2->next)
		{
			if(ptr2->vis == 0 && dp(ptr->idx, ptr2->idx))
			{
				flag = 1;
				ptr2->vis = 1;
				break;
			}
		}
		if(!flag) return f[a][b] = 0;
	}
	return f[a][b];
}

void solve()
{
	if(len != strlen(t))
	{
		puts("different");
		return;
	}

	/*
	for(int i=0; i<n; ++i)
	{
		printf("%d : ", i);
		for(Edge *ptr=adj2[i].next; ptr; ptr=ptr->next)
		{
			printf("%d ", ptr->idx);
		}
		puts("");
	}
	*/

	memset(f, -1, sizeof f);

	if(dp(0, 0)) puts("same");
	else puts("different");
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

