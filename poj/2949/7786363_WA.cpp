/*
 * =======================================================
 *       Filename:  2949.cpp
 *    Description:  
 *        Created:  25/10/10 00:35:20
 *         Author:  hust_zuma
 * =======================================================
 */
#include <stdio.h>
#include <cstring>
#define maxl 1020
#define SIZE 2010
#define eps 1e-5

int tot = 676;

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl], memo[1000010];

int n, m, mset, Q[SIZE + 10], head, tail;
double d[maxl], max_len;
int in[maxl], cnt[maxl];
char str[10000];

int getid(char c1, char c2)
{
	return (c1 - 'a') * 26 + c2 - 'a';
}

void addEdge(int a, int b, int c)
{
	Edge *ptr = &memo[mset++];
	ptr->idx = b; ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<tot; ++i) adj[i].next = NULL;
	
	for(int i=1; i<=n; ++i)
	{
		scanf("%s", str);
		int len = strlen(str);
		addEdge(getid(str[0], str[1]), getid(str[len-2], str[len-1]), len);
	}
}

bool hasNCircle(double x)
{
	head = tail = 0;
	for(int i=0; i<tot; ++i)
	{
		d[i] = 0.0;
		in[i] = 1;
		cnt[i] = 1;
		Q[tail++] = i;
	}

	while(head != tail)
	{
		int u = Q[head++];
		if(head == SIZE) head = 0;
		in[u] = 0;

		for(Edge *ptr=adj[u].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(d[u] + ptr->len - x < d[v])
			{
				d[v] = d[u] + ptr->len - x;
				if(!in[v])
				{
					in[v] = 1;
					Q[tail++] = v;
					if(tail == SIZE) tail = 0;
					cnt[v]++;
					if(cnt[v] >= tot)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void solve()
{
	double l = 0.0, r = 1e20, mid, ans;
	while(l < r + eps)
	{
		mid = (l + r) / 2.0;
		if(hasNCircle(mid))
		{
			ans = mid;
			r = mid - eps;
		}
		else l = mid + eps;
	}
	printf("%.5lf\n", ans);
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

