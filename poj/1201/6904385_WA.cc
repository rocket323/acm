#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 50005
#define INF 0x3f3f3f3f

struct Edge
{
	int idx, len;
	Edge *next;
}
adj[maxl + 20], memo[maxl * 10];

int d[maxl + 20], mset, n, a, b, c;
int Q[maxl + 20], head, tail, in[maxl + 20];

void addEdge(int a, int b, int c)
{
	//if(b < 6) printf("e %d %d %d\n", a, b, c);
	Edge *ptr = &memo[mset++];
	ptr->idx = b;
	ptr->len = c;
	ptr->next = adj[a].next;
	adj[a].next = ptr;
}

void init()
{
	mset = 0;
	for(int i=0; i<=maxl; ++i) adj[i].next = NULL;

	for(int i=1; i<maxl; ++i) addEdge(i + 1, i, 0), addEdge(i, i + 1, 1);
	for(int i=1; i<=maxl; ++i) addEdge(0, i, 0);

	for(int i=0; i<n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		a += 2; b += 2;
		addEdge(b, a - 1, -c);
	}
}

void spfa()
{
	head = tail = 0;
	Q[tail++] = 0;

	memset(in, 0, sizeof in);
	memset(d, 0x3f, sizeof d);
	in[0] = 1;
	d[0] = 0;

	while(head < tail)
	{
		int k = Q[head];
		head = (head + 1) % (maxl + 5);
		in[k] = 0;

		for(Edge *ptr=adj[k].next; ptr; ptr=ptr->next)
		{
			int v = ptr->idx;
			if(d[k] + ptr->len < d[v])
			{
				d[v] = d[k] + ptr->len;
				if(!in[v])
				{
					in[v] = 1;
					Q[tail] = v;
					tail = (tail + 1) % (maxl + 5);
				}
			}
		}
	}
}

void solve()
{
	
	/*
	for(int i=0; i<=6; ++i)
	{
		printf("%d : ", i);
		for(Edge *ptr=adj[i].next; ptr; ptr=ptr->next)
		{
			printf("%d ", ptr->idx);
		}
		puts("");
	}
	*/

	spfa();
	
	int min_dist = INF;
	for(int i=0; i<=maxl; ++i) min_dist = min(min_dist, d[i]);
	if(min_dist > 0) min_dist = 0;

	//for(int i=0; i<=6; ++i) printf("%d %d\n", i, d[i]);

	//printf("%d %d %d\n", min_dist, d[maxl], d[maxl] - min_dist);
	printf("%d\n", d[maxl] - d[1]);
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

